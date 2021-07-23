/* 
 * Pico SDVX
 * @author SpeedyPotato
 * 
 * Based off dev_hid_composite and mdxtinkernick/pico_encoders
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "pico/stdlib.h"

#include "usb_descriptors.h"

#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "encoders.pio.h"

#define SW_GPIO_SIZE 10  // Number of switches
#define ENC_GPIO_SIZE 2 // Number of encoders


////////////////////////////////////////////////
#define SPI_PORT0 spi0
#define SPI_PORT1 spi1
#define SPI_PORT2 spi2
#define SPI_PORT3 spi3

const uint MISO = 4;
const uint MOSI = 3;
const uint CS = 5;
const uint SCK = 2;

const uint ADC1 = 25;
const uint ADC2 = 24;
const uint button1 = 8;
const uint button2 = 9;


#define BASE 200
#define SPI_CHAN 0
///////////////////////////////////////////////

// MODIFY KEYBINDS HERE, MAKE SURE LENGTH MATCHES SW_GPIO_SIZE
const uint8_t SW_KEYCODE[] =
    { HID_KEY_W, HID_KEY_S, HID_KEY_A, HID_KEY_D, HID_KEY_I, HID_KEY_K, HID_KEY_J, HID_KEY_L, HID_KEY_R, HID_KEY_SPACE};
//const uint8_t SW_GPIO[] = {4, 5, 6, 7, 8, 9, 10};           // MAKE SURE LENGTH MATCHES SW_GPIO_SIZE
const uint8_t LED_GPIO[] = {28, 27, 26, 22, 21, 20, 19};    // MAKE SURE LENGTH MATCHES SW_GPIO_SIZE
const uint8_t ENC_GPIO[] = {0, 2};      // L_ENC(0, 1); R_ENC(2, 3)
const uint8_t ENC_SENS = 1;        // Encoder sensitivity multiplier

PIO pio;
uint32_t enc_val[2];
uint32_t prev_enc_val[2];
bool enc_changed;
bool pressed[SW_GPIO_SIZE];
bool sw_val[SW_GPIO_SIZE];
bool prev_sw_val[SW_GPIO_SIZE];
bool sw_changed;

///////////////////////////////////////////////////
int32_t t_fine;
uint16_t dig_T1;
int16_t dig_T2, dig_T3;

int32_t compTemp(int32_t adc_T){
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3)) >> 14;

    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

void read_temp_comp(){
    uint8_t buffer[6], reg;

    reg = 0x88 | 0x80;
    gpio_put(CS, 0);
    spi_write_blocking(SPI_PORT0, &reg, 1);
    spi_read_blocking(SPI_PORT0, 0, buffer, 6);
    gpio_put(CS, 1);

    dig_T1 = buffer[0] | (buffer[1] << 8);
    dig_T2 = buffer[2] | (buffer[3] << 8);
    dig_T3 = buffer[4] | (buffer[5] << 8);
}
static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(CS, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(CS, 1);
    asm volatile("nop \n nop \n nop");
}
//////////////////////////////////////////////////

/**
 * DMA Encoder Logic
 **/
void dma_handler() {
    uint i = 1;
    int interrupt_channel = 0; 
    while ((i & dma_hw->ints0) == 0) {  
        i = i << 1; 
        ++interrupt_channel; 
    }  
    dma_hw->ints0 = 1u << interrupt_channel;
    if (interrupt_channel < 4) {
        dma_channel_set_read_addr(interrupt_channel, &pio->rxf[interrupt_channel], true);
    }
}

/**
 * Initialize Board Pins
 **/
void init() {
    // LED Pin on when connected
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, 1);

    // Set up the state machine for encoders
    pio = pio0;
    uint offset = pio_add_program(pio, &encoders_program);
    // Setup Encoders
    for (int i = 0; i < ENC_GPIO_SIZE; i++){
        enc_val[i] = 0;
        prev_enc_val[i] = 0;
        encoders_program_init(pio, i, offset, ENC_GPIO[i]);
        
        dma_channel_config c = dma_channel_get_default_config(i);
        channel_config_set_read_increment(&c, false);
        channel_config_set_write_increment(&c, false);
        channel_config_set_dreq(&c, pio_get_dreq(pio, i, false));
        
        dma_channel_configure(i, &c,
            &enc_val[i],        // Destinatinon pointer
            &pio->rxf[i],      // Source pointer
            0x10, // Number of transfers
            true                // Start immediately
        );
        irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
        irq_set_enabled(DMA_IRQ_0, true);
        dma_channel_set_irq0_enabled(i, true);
    }

    // Setup Button GPIO
    for (int i = 0; i < SW_GPIO_SIZE; i++) {
        sw_val[i] = false;
        prev_sw_val[i] = false;
        //gpio_init(SW_GPIO[i]);
        //gpio_set_function(SW_GPIO[i], GPIO_FUNC_SIO);
        //gpio_set_dir(SW_GPIO[i], GPIO_IN);
        //gpio_pull_up(SW_GPIO[i]);
    }

    // Setup LED GPIO
    for (int i = 0; i < SW_GPIO_SIZE; i++) {
        gpio_init(LED_GPIO[i]);
        gpio_set_dir(LED_GPIO[i], GPIO_OUT);
    }

    // Set listener bools
    enc_changed = false;
    sw_changed = false;
}

/**
 * Update Class Vars
 **/
void update_inputs() {
    // Encoder Flag
    for (int i = 0; i < ENC_GPIO_SIZE; i++) {
        if (enc_val[i] != prev_enc_val[i]) {
            enc_changed = true;
            break;
        }
    }
    // Switch Update & Flag
    for (int i = 0; i < SW_GPIO_SIZE; i++) {
        if (sw_val[i]) {
            sw_val[i] = true;
        }else {
            sw_val[i] = false;
        }
        if (!sw_changed && sw_val[i] != prev_sw_val[i]) {
            sw_changed = true;
        }
    }
}

/**
 * Keyboard Mode
 **/
void key_mode() {
    if (tud_hid_ready()) {
        /*------------- Keyboard -------------*/
        if (sw_changed) {
            bool is_pressed = false;
            int keycode_idx = 0;
            uint8_t keycode[6] = {0};   //looks like we are limited to 6kro?
            for (int i = 0; i < SW_GPIO_SIZE; i++) {
                if (sw_val[i]) {
                    // use to avoid send multiple consecutive zero report for keyboard
                    keycode[keycode_idx] = SW_KEYCODE[i];
                    keycode_idx = ++keycode_idx % SW_GPIO_SIZE;
                    is_pressed = true;

                    prev_sw_val[i] = sw_val[i];
                    // Reactive Lighting On
                    gpio_put(LED_GPIO[i], 1);
                } else {
                    // Reactive Lighting Off
                    gpio_put(LED_GPIO[i], 0);
                }
            }
            if (is_pressed) {
                // Send key report
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
            } else {
                // Send empty key report if previously has key pressed
                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            }
            sw_changed = false;
        }

        /*------------- Mouse -------------*/
       /* if (enc_changed) {
            // Delay if needed before attempt to send mouse report
            while (!tud_hid_ready()) {
                board_delay(1);
            }
            tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, (enc_val[0] - prev_enc_val[0]) * ENC_SENS,
                                                        (enc_val[1] - prev_enc_val[1]) * ENC_SENS, 0, 0);
            for (int i = 0; i < ENC_GPIO_SIZE; i++) {
                prev_enc_val[i] = enc_val[i];
            }
            enc_changed = false;
        }
        */
    }
}

/**
 * Main Loop Function
 **/
int main(void) {
    board_init();
    tusb_init();
    init();
///////////////////////////////////////////////////
    spi_init(SPI_PORT0, 115200);    // Initialize spi0 at 115200 Hz
    // spi_init(SPI_PORT1, 115200);    // Initialize spi1 at 115200 Hz
    spi_set_format(SPI_PORT0, 8, 0, 0, SPI_MSB_FIRST);
    // spi_set_format(SPI_PORT1, 8, 0, 0, SPI_MSB_FIRST);

    // Initialize GPIO pins for SPI communication
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(SCK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);

    // Configure Chip Select
    gpio_init(CS);                  // Initialize CS pin
    gpio_set_dir(CS, GPIO_OUT);     // Set CS as Output.
    gpio_put(CS, 1);                // Set CS High to indicate no current SPI communication


    adc_init();
    gpio_init(button1);
    gpio_set_dir(button1, GPIO_IN);
    gpio_pull_up(button1);

    gpio_init(button2);
    gpio_set_dir(button2, GPIO_IN);
    gpio_pull_up(button2);


    int32_t temperature, rawtemp;
    uint8_t reg, buffer1[3], buffer2[3],buffer3[3],buffer4[3];
///////////////////////////////////////////////////





    while (1) {
        cs_select();

        int chan = 0;
        size_t len = 3;
        buffer1[0] = 0x06 | ((chan & 0x07) >> 7);
        buffer1[1] = ((chan & 0x07) << 6);
        buffer1[2] = 0x00;

        uint8_t returnData1[3];
        // uint8_t returnData2[10];

        spi_write_read_blocking(SPI_PORT0, buffer1, returnData1, 3);
        // spi_write_read_blocking(SPI_PORT1, buffer2, returnData2, sizeof(buffer2));

        returnData1[1] = 0x0F & returnData1[1];
        int x_1 = (returnData1[1] << 8) | returnData1[2];

        float val1 = (3.3 / 4096.0) * x_1;
        // float val2 = (3.3 / 1023.0 ) * y_1;

        cs_deselect();
///////////////////////////////////////////////////////
        cs_select();

        chan = 1;
        buffer2[0] = 0x06 | ((chan & 0x07) >> 7);
        buffer2[1] = ((chan & 0x07) << 6);
        buffer2[2] = 0x00;

        uint8_t returnData2[3];

        spi_write_read_blocking(SPI_PORT0, buffer2, returnData2, 3);

        returnData2[1] = 0x0F & returnData2[1];
        int y_1 = (returnData2[1] << 8) | returnData2[2];

        float val2 = (3.3 / 4096.0) * y_1;

        cs_deselect();

///////////////////////////////////////////////////////////
 cs_select();

        chan = 2;

        buffer3[0] = 0x06 | ((chan & 0x07) >> 7);
        buffer3[1] = ((chan & 0x07) << 6);
        buffer3[2] = 0x00;

        uint8_t returnData3[3];
        // uint8_t returnData2[10];

        spi_write_read_blocking(SPI_PORT0, buffer3, returnData3, 3);
        // spi_write_read_blocking(SPI_PORT1, buffer2, returnData2, sizeof(buffer2));

        returnData3[1] = 0x0F & returnData3[1];
        int x_2 = (returnData3[1] << 8) | returnData3[2];

        float val3 = (3.3 / 4096.0) * x_2;
        // float val2 = (3.3 / 1023.0 ) * y_1;

        cs_deselect();
///////////////////////////////////////////////////////
        cs_select();

        chan = 3;
        buffer4[0] = 0x06 | ((chan & 0x07) >> 7);
        buffer4[1] = ((chan & 0x07) << 6);
        buffer4[2] = 0x00;

        uint8_t returnData4[3];

        spi_write_read_blocking(SPI_PORT0, buffer4, returnData4, 3);

        returnData4[1] = 0x0F & returnData4[1];
        int y_2 = (returnData4[1] << 8) | returnData4[2];

        float val4 = (3.3 / 4096.0) * y_2;

        cs_deselect();
/*
        adc_select_input(ADC2);
        uint16_t x_2 = adc_read();
        adc_select_input(ADC1);
        uint16_t y_2 = adc_read();
  */     
        bool pressed1 = gpio_get(button1);
        bool pressed2 = gpio_get(button2);
        

        if (y_1 < 1000) {
              sw_val[0]=true; // Ascend
        }
        else if (y_1 > 3000) {
               sw_val[1]=true;// Descend
        }
        else {
            sw_val[0]=false;
            sw_val[1]=false;
        }
        if (x_1 > 3000) {
            sw_val[2]=true; // Look left
        }
        else if (x_1 < 1000) {
            sw_val[3]=true;// Look Right
        }
        else {
            sw_val[3]=false;
            sw_val[2]=false;
        }
        if (y_2 < 1000) {
            sw_val[4]=true;// Forward
        }
        else if (y_2 > 3000) {
            sw_val[5]=true;// Backward
        }
        else {
            sw_val[4]=false;
            sw_val[5]=false;
            
        }
        if (x_2 > 3000) {
            sw_val[6]=true;// Lean left
        }
        else if (x_2 < 1000) {
            sw_val[7]=true;// Lean Right
        }
        else {
            sw_val[6]=false;
            sw_val[7]=false;
        }

        if (!pressed1) {
            sw_val[8]=true;// Reset
        }
        else {
            sw_val[8]=false;// Reset
        }
        if (!pressed2) {
            sw_val[9]=true;
        }
        else {
            sw_val[9]=false;// Reset
        }
        //sleep_ms(10);
        tud_task(); // tinyusb device task
        update_inputs();
        key_mode();
    }

    return 0;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
    // TODO not Implemented
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
    // TODO set LED based on CAPLOCK, NUMLOCK etc...
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}
