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
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "encoders.pio.h"

#define SW_GPIO_SIZE 10  // Number of switches
#define ENC_GPIO_SIZE 2 // Number of encoders




// MODIFY KEYBINDS HERE, MAKE SURE LENGTH MATCHES SW_GPIO_SIZE
const uint8_t SW_KEYCODE[] =
    { HID_KEY_W, HID_KEY_S, HID_KEY_A, HID_KEY_D, HID_KEY_I, HID_KEY_K, HID_KEY_J, HID_KEY_L, HID_KEY_R, HID_KEY_SPACE};

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
const uint ADC= 26;
const uint button1= 14;
const uint button2= 15;
static int addr = 0x68;
#define ONN 1
#define OFF 0

#define R_LED 16
#define G_LED 17
#define B_LED 18


#ifdef i2c_default
static void mpu6050_reset() {
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}

static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    i2c_write_blocking(i2c_default, addr, &val, 1, true); // true to keep master control of bus
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    // Now temperature from reg 0x41 for 2 bytes
    // The register is auto incrementing on each read
    val = 0x41;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 2, false);  // False - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}
#endif
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
   //stdio_init_all();
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/mpu6050_i2c example requires a board with I2C pins
    //puts("Default I2C pins were not defined");
#else
    //printf("Hello, MPU6050! Reading raw data from registers...\n");

    int flag=0;
    
    bool pressed_temp;
    bool pressed1_temp;
    bool pressed1;
    bool pressed2;
    
    adc_init();
    gpio_init(button1);
    gpio_set_dir(button1,GPIO_IN);
    gpio_pull_up(button1);

    gpio_init(button2);
    gpio_set_dir(button2,GPIO_IN);
    gpio_pull_up(button2);
    

    gpio_init(R_LED);
    gpio_init(G_LED);
    gpio_init(B_LED);
    gpio_set_dir(R_LED,GPIO_OUT);
    gpio_set_dir(G_LED,GPIO_OUT);
    gpio_set_dir(B_LED,GPIO_OUT);

	gpio_put(R_LED,ONN);
	gpio_put(G_LED,ONN);

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    mpu6050_reset();

    int16_t acceleration[3], gyro[3], temp;

///////////////////////////////////////////////////

    while (1) {      
        mpu6050_read_raw(acceleration, gyro, &temp);


        adc_select_input(24);
        uint16_t flex_val= adc_read();
        pressed1 = gpio_get(button1);
        pressed2 = gpio_get(button2);

        if(!pressed2 && pressed_temp){

        	if(flag == 0){
        		gpio_put(R_LED,OFF);
        		gpio_put(G_LED,OFF);
        		flag=1;
        		gpio_put(R_LED,ONN);
        		gpio_put(B_LED,ONN);
           	}
        	else if (flag == 1){
        		gpio_put(R_LED,OFF);
        		gpio_put(B_LED,OFF);
        		flag=2;
        		gpio_put(G_LED,ONN);
        		gpio_put(B_LED,ONN);
        	}
        	else if (flag == 2){
        		gpio_put(G_LED,OFF);
        		gpio_put(B_LED,OFF);
        		flag=1;
        		gpio_put(R_LED,ONN);
        		gpio_put(B_LED,ONN);
        	}
        }
        pressed_temp=pressed2;
        if(!pressed1 && pressed1_temp){
			gpio_put(G_LED,OFF);
			gpio_put(B_LED,OFF);
			gpio_put(R_LED,OFF);
			flag=0;
			gpio_put(G_LED,ONN);
			gpio_put(R_LED,ONN);
        }
        pressed1_temp = pressed1;
        //FLEX VALUES
        //Ascend Descend
        if(flag==1 && flex_val > 2850){
        	sw_val[0]=true;
        }
        else if(flag==2 && flex_val > 2850){
        	sw_val[1]=true;
        }else{
        	sw_val[0]=false;
            sw_val[1]=false;	
        }

		double leanTemp=0;
       // look left Right
        if(acceleration[1] < -5000 && acceleration[1]> -17000){
			leanTemp = ((float)acceleration[1])/10000;
			if(leanTemp < -1.0)
				leanTemp=-1.0;
        	sw_val[2]=true;
            sw_val[6]=true;
        }
        else if(acceleration[1] > 5000 && acceleration[1] < 17000){
        	leanTemp = ((float)acceleration[1])/10000;
			if(leanTemp > 1.0)
				leanTemp=1.0;
        	sw_val[3]=true;
            sw_val[7]=true;
        }else{
        	sw_val[3]=false;
            sw_val[2]=false;
            sw_val[6]=false;
            sw_val[7]=false;	
        }


        //Forward Backward
        if(acceleration[0] > 5000 && acceleration[0] < 17000){
        	leanTemp = ((float)acceleration[0])/10000;
			if(leanTemp > 1.0)
				leanTemp=1.0;

			leanTemp *=-1.0;
        	sw_val[5]=true;
        }
        else if(acceleration[0] < -5000 && acceleration[0]> -17000){
        	leanTemp = ((float)acceleration[0])/10000;
			if(leanTemp < -1.0)
				leanTemp=-1.0;
			leanTemp *=-1.0;
        	sw_val[4]=true;
        }else{
        	sw_val[4]=false;
            sw_val[5]=false;	
        }
        



        //Reset
        if(!pressed1 ){
        	sw_val[8]=true;

        }else
        	sw_val[8]=false;



        

        //start
        sw_val[9]=false;
///////////////////////////////////////////////////////

        tud_task(); // tinyusb device task
        update_inputs();
        key_mode();
    }
#endif
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
