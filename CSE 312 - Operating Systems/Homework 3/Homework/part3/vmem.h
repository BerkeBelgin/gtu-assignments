#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define TNAME_FILL "fill"
#define TNAME_QUICK "quick"
#define TNAME_BUBBLE "bubble"
#define TNAME_MERGE "merge"
#define TNAME_LINEAR "linear"
#define TNAME_BINARY "binary"

#define TREP_NRU "NRU"
#define TREP_FIFO "FIFO"
#define TREP_SC "SC"
#define TREP_LRU "LRU"
#define TREP_WSC "WSClock"

#define TTYPE_REGULAR "regular"
#define TTYPE_INVERTED "inverted"

#define FILENAME_SIZE 64

enum table_rep_alg {
    NRU,
    FIFO,
    SC, 
    LRU, 
    WSC
};

enum table_type {
    REG,
    INV
};

struct tbl_ent {
    unsigned int address;
    unsigned short reference_bit;
    unsigned short modified_bit;
    unsigned short present;
};

struct vir_mem {
    unsigned int page_size;
    unsigned int mem_page_c;
    unsigned int f_page_c;
    unsigned int tbl_page_c;

    char filename[FILENAME_SIZE];

    int *mp;
    FILE *fp;
    struct tbl_ent *tp;

    enum table_type table_type;
    enum table_rep_alg table_rep_alg;
    unsigned int table_print_intrvl;

    queue_t *fifo_q;
    unsigned short *sc_l;
    unsigned int *lru_l;
    unsigned long *wsc_l;

    unsigned int wsc_hand;
    unsigned long wsc_time;

    unsigned long stat_read[6];
    unsigned long stat_write[6];
    unsigned long stat_page_miss[6];
    unsigned long stat_page_replacement[6];
    unsigned long stat_disk_page_read[6];
    unsigned long stat_disk_page_write[6];
};

extern struct vir_mem vm;

static int h_pow(int x, unsigned int n){
    if(n <= 0)
        return 1;
    else 
        return x * h_pow(x, n-1);
}

static void int_from_str(int *num, unsigned char *str, unsigned int sizeof_int, unsigned int sizeof_char){
    *num = 0;
    for(int i = 0; i < (sizeof_int / sizeof_char); i++){
        *num = *num | str[i] << ((sizeof_int - (i+1) * sizeof_char) * 8);
    }
}

static void int_to_str(int *num, unsigned char *str, unsigned int sizeof_int, unsigned int sizeof_char){
    for(int i = 0; i < (sizeof_int / sizeof_char); i++){
        str[i] = (*num >> ((sizeof_int - (i+1) * sizeof_char) * 8)) & 0xFF;
    }
}

static void get_page_mem(unsigned int page_c, int *mp, unsigned int page_index, unsigned int page_size, int *vals){
    if(page_index < page_c){
        for(int i = 0; i < page_size; i++){
            vals[i] = mp[page_index * page_size + i];
        }
    }
}

static void get_page_f(unsigned int page_c, FILE *fp, unsigned int page_index, unsigned int page_size, int *vals){
    if(page_index < page_c){
        unsigned char buff[sizeof(int)/sizeof(char)];
        fseek(fp, page_index * page_size * (sizeof(int)/sizeof(char)), SEEK_SET);
        for(int i = 0; i < page_size; i++){
            fread(buff, sizeof(int)/sizeof(char), 1, fp);
            int_from_str(&(vals[i]), buff, sizeof(int), sizeof(char));
        }
    }
}

static void set_page_mem(unsigned int page_c, int *mp, unsigned int page_index, unsigned int page_size, int *vals){
    if(page_index < page_c){
        for(int i = 0; i < page_size; i++){
            mp[page_index * page_size + i] = vals[i];
        }
    }
}

static void set_page_f(unsigned int page_c, FILE *fp, unsigned int page_index, unsigned int page_size, int *vals){
    if(page_index < page_c){
        unsigned char buff[sizeof(int)/sizeof(char)];
        fseek(fp, page_index * page_size * (sizeof(int)/sizeof(char)), SEEK_SET);
        for(int i = 0; i < page_size; i++){
            int_to_str(&(vals[i]), buff, sizeof(int), sizeof(char));
            fwrite(buff, sizeof(int)/sizeof(char), 1, fp);
        }
    }
}

void vir_mem_create(unsigned int frameSize, unsigned int numPhysical, unsigned int numVirtual, char *pageReplacement, char *tableType, unsigned int pageTablePrintInt, char *filename){
    vm.page_size  = h_pow(2, frameSize);
    vm.mem_page_c = h_pow(2, numPhysical);
    vm.f_page_c   = h_pow(2, numVirtual) - vm.mem_page_c;
    memset(vm.filename, '\0', FILENAME_SIZE);
    strcpy(vm.filename, filename);

    if(strcmp(pageReplacement, TREP_NRU ) == 0) 
        vm.table_rep_alg = NRU;
    else if(strcmp(pageReplacement, TREP_FIFO ) == 0) 
        vm.table_rep_alg = FIFO;
    else if(strcmp(pageReplacement, TREP_SC ) == 0) 
        vm.table_rep_alg = SC;
    else if(strcmp(pageReplacement, TREP_LRU) == 0) 
        vm.table_rep_alg = LRU;
    else if(strcmp(pageReplacement, TREP_WSC) == 0) 
        vm.table_rep_alg = WSC;
    else 
        vm.table_rep_alg = LRU;
    
    if(strcmp(tableType, TTYPE_REGULAR) == 0) 
        vm.table_type = REG;
    else if(strcmp(tableType, TTYPE_INVERTED) == 0) 
        vm.table_type = INV;
    else 
        vm.table_type = REG;

    vm.table_print_intrvl = pageTablePrintInt;

    vm.mp = (int *) malloc(sizeof(int) * vm.page_size * vm.mem_page_c);
    for(int i = 0; i < (vm.page_size * vm.mem_page_c); i++)
        vm.mp[i] = 0;

    unsigned char buff[sizeof(int)/sizeof(char)];
    int val = -1;

    vm.fp = fopen(filename, "w+");
    for(int i = 0; i < (vm.page_size * vm.f_page_c); i++){
        int_to_str(&val, buff, sizeof(int), sizeof(char));
        fwrite(buff, sizeof(int)/sizeof(char), 1, vm.fp);
    }
    rewind(vm.fp);

    if(vm.table_type == REG){
        vm.tbl_page_c = (vm.mem_page_c + vm.f_page_c);
        vm.tp = (struct tbl_ent *) malloc(sizeof(struct tbl_ent) * vm.tbl_page_c);
        for(int i = 0; i < vm.mem_page_c; i++){
            vm.tp[i].address = i * vm.page_size;
            vm.tp[i].reference_bit = 0;
            vm.tp[i].modified_bit = 0;
            vm.tp[i].present = 1;
        }
        for(int i = 0; i < vm.f_page_c; i++){
            vm.tp[vm.mem_page_c + i].address = i * vm.page_size;
            vm.tp[vm.mem_page_c + i].reference_bit = 0;
            vm.tp[vm.mem_page_c + i].modified_bit = 0;
            vm.tp[vm.mem_page_c + i].present = 0;
        }
    } else {
        vm.tbl_page_c = vm.mem_page_c;
        vm.tp = (struct tbl_ent *) malloc(sizeof(struct tbl_ent) * vm.tbl_page_c);
        for(int i = 0; i < vm.mem_page_c; i++){
            vm.tp[i].address = i * vm.page_size;
            vm.tp[i].reference_bit = 0;
            vm.tp[i].modified_bit = 0;
            vm.tp[i].present = 1;
        }
    }

    if(vm.table_rep_alg == FIFO) {
        vm.fifo_q = (queue_t *) malloc(sizeof(queue_t));
        init_queue(vm.fifo_q);
        for(int i = 0; i < vm.mem_page_c; i++){
            enqueue(vm.fifo_q, i);
        }
    } else if(vm.table_rep_alg == SC){
        vm.sc_l = (unsigned short *) malloc(sizeof(unsigned short) * vm.mem_page_c);
        for(int i = 0; i < vm.mem_page_c; i++){
            vm.sc_l[i] = 0;
        }
    } else if(vm.table_rep_alg == LRU){
        vm.lru_l = (unsigned int *) malloc(sizeof(unsigned int) * vm.mem_page_c);
        for(int i = 0; i < vm.mem_page_c; i++){
            vm.lru_l[i] = i;
        }
    } else if(vm.table_rep_alg == WSC) {
        vm.wsc_hand = 0;
        vm.wsc_time = 0;
        vm.wsc_l = (unsigned long *) malloc(sizeof(unsigned long) * vm.tbl_page_c);
        for(int i = 0; i < vm.mem_page_c; i++){
            vm.wsc_l[i] = i;
            vm.wsc_time += 1;
        }
    }
    
    for(int i = 0; i < 6; i++){
        vm.stat_read[i] = 0;
        vm.stat_write[i] = 0;
        vm.stat_page_miss[i] = 0;
        vm.stat_page_replacement[i] = 0;
        vm.stat_disk_page_read[i] = 0;
        vm.stat_disk_page_write[i] = 0;
    }
}

void vir_mem_destroy(){
    free(vm.mp);
    fclose(vm.fp);
    remove(vm.filename);
    free(vm.tp);
    
    if(vm.table_rep_alg == FIFO) {
        clear_queue(vm.fifo_q);
        free(vm.fifo_q);
    } else if(vm.table_rep_alg == SC){
        free(vm.sc_l);
    } else if(vm.table_rep_alg == LRU){
        free(vm.lru_l);
    } else if(vm.table_rep_alg == WSC) {
        free(vm.wsc_l);
    }
}

static void swap_page_reg(unsigned int vir_p_idx_mem, unsigned int vir_p_idx_f, struct vir_mem *vm){
    if(vir_p_idx_mem < (vm->mem_page_c + vm->f_page_c) && vir_p_idx_f < (vm->mem_page_c + vm->f_page_c) && vir_p_idx_mem != vir_p_idx_f){
        int buff_m[vm->page_size];
        int buff_f[vm->page_size];

        int mem_address = vm->tp[vir_p_idx_mem].address;
        int f_address = vm->tp[vir_p_idx_f].address;

        int mem_p_address = vm->tp[vir_p_idx_mem].address / vm->page_size;
        int f_p_address = vm->tp[vir_p_idx_f].address / vm->page_size;

        get_page_mem(vm->mem_page_c, vm->mp, mem_p_address, vm->page_size, buff_m);
        get_page_f(vm->f_page_c, vm->fp, f_p_address, vm->page_size, buff_f);
        set_page_mem(vm->mem_page_c, vm->mp, mem_p_address, vm->page_size, buff_f);
        set_page_f(vm->f_page_c, vm->fp, f_p_address, vm->page_size, buff_m);

        vm->tp[vir_p_idx_mem].address = f_address;
        vm->tp[vir_p_idx_mem].modified_bit = 0;
        vm->tp[vir_p_idx_mem].reference_bit = 0;
        vm->tp[vir_p_idx_mem].present = 0;

        vm->tp[vir_p_idx_f].address = mem_address;
        vm->tp[vir_p_idx_f].modified_bit = 0;
        vm->tp[vir_p_idx_f].reference_bit = 0;
        vm->tp[vir_p_idx_f].present = 1;
    }
}

static void swap_page_inv(unsigned int vir_p_idx_mem, unsigned int vir_p_idx_f, struct vir_mem *vm){
    if(vir_p_idx_mem < (vm->mem_page_c + vm->f_page_c) && vir_p_idx_f < (vm->mem_page_c + vm->f_page_c) && vir_p_idx_mem != vir_p_idx_f){
        int mem_page_in = -1;
        int mem_page_out = -1;
        int f_page_in = -1;
        int f_page_out = -1;

        for(int v = 0, m = 0, f = 0; v < (vm->mem_page_c + vm->f_page_c); v++){
            if(v == vir_p_idx_mem){
                mem_page_out = m;
                if(vir_p_idx_mem < vir_p_idx_f)f_page_in = f;
                else f_page_in = f-1;
            } else if(v == vir_p_idx_f){
                f_page_out = f;
                if(vir_p_idx_f < vir_p_idx_mem)mem_page_in = m;
                else mem_page_in = m-1;
            }

            if(m >= vm->mem_page_c){
                f++;
            } else if(f >= vm->f_page_c){
                m++;
            } else {
                if((vm->tp[m].address / vm->page_size) > v)f++;
                else m++;
            }
        }

        int buff_m[vm->page_size];
        int buff_f[vm->page_size];
        
        get_page_mem(vm->mem_page_c, vm->mp, mem_page_out, vm->page_size, buff_m);
        get_page_f(vm->f_page_c, vm->fp, f_page_out, vm->page_size, buff_f);

        int tmp[vm->page_size];
        if(mem_page_out < mem_page_in){
            for(int i = mem_page_out; i < mem_page_in; i++){
                get_page_mem(vm->mem_page_c, vm->mp, i+1, vm->page_size, tmp);
                set_page_mem(vm->mem_page_c, vm->mp, i, vm->page_size, tmp);

                vm->tp[i].address       = vm->tp[i+1].address;
                vm->tp[i].modified_bit  = vm->tp[i+1].modified_bit;
                vm->tp[i].reference_bit = vm->tp[i+1].reference_bit;
                vm->tp[i].present       = vm->tp[i+1].present;
            }
        } else if(mem_page_in < mem_page_out) {
            for(int i = mem_page_out; i > mem_page_in; i--){
                get_page_mem(vm->mem_page_c, vm->mp, i-1, vm->page_size, tmp);
                set_page_mem(vm->mem_page_c, vm->mp, i, vm->page_size, tmp);

                vm->tp[i].address       = vm->tp[i-1].address;
                vm->tp[i].modified_bit  = vm->tp[i-1].modified_bit;
                vm->tp[i].reference_bit = vm->tp[i-1].reference_bit;
                vm->tp[i].present       = vm->tp[i-1].present;
            }
        }

        if(f_page_out < f_page_in){
            for(int i = f_page_out; i < f_page_in; i++){
                get_page_f(vm->f_page_c, vm->fp, i+1, vm->page_size, tmp);
                set_page_f(vm->f_page_c, vm->fp, i, vm->page_size, tmp);
            }
        } else if(f_page_in < f_page_out) {
            for(int i = f_page_out; i > f_page_in; i--){
                get_page_f(vm->f_page_c, vm->fp, i-1, vm->page_size, tmp);
                set_page_f(vm->f_page_c, vm->fp, i, vm->page_size, tmp);
            }
        }

        set_page_mem(vm->mem_page_c, vm->mp, mem_page_in, vm->page_size, buff_f);
        set_page_f(vm->f_page_c, vm->fp, f_page_in, vm->page_size, buff_m);

        vm->tp[mem_page_in].address = vir_p_idx_f * vm->page_size;
        vm->tp[mem_page_in].modified_bit = 0;
        vm->tp[mem_page_in].reference_bit = 0;
        vm->tp[mem_page_in].present = 1;
    }
}

static int is_present_reg(unsigned int v_page_index, unsigned int tbl_page_c, struct tbl_ent *tp){
    return tp[v_page_index].present;
}

static int is_present_inv(unsigned int v_page_index, unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int page_size){
    for(int i = 0; i < tbl_page_c && tp[i].address <= v_page_index * page_size; i++){
        if(tp[i].address == v_page_index * page_size) return 1;
    }
    return 0;
}

static int find_mem_page_idx_inv(unsigned int v_page_idx, unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int page_size){
    for(int i = 0; i < tbl_page_c; i++){
        if(tp[i].address == (v_page_idx * page_size)) return i;
    }
    return -1;
}

static int find_v_page_idx_reg(unsigned int mem_page_idx, unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int page_size){
    for(int i = 0; i < tbl_page_c; i++){
        if(tp[i].present != 0 && tp[i].address == (mem_page_idx * page_size)) return i;
    }
    return -1;
}

static int lru_find_page_idx(unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int mem_page_c, unsigned int *lru_l, unsigned int page_size, enum table_type table_type){
    int idx = -1;

    for(int i = 0; i < mem_page_c; i++){
        if(lru_l[i] == 0){
            idx = i;
            lru_l[i] = mem_page_c - 1;
        } else {
            lru_l[i] -= 1;
        }
    }
    
    if(table_type == REG){
        return find_v_page_idx_reg(idx, tbl_page_c, tp, page_size);
    } else {
        return (tp[idx].address / page_size);
    }
}

static void lru_update_page_idx(unsigned int v_page_idx, unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int mem_page_c, unsigned int *lru_l, unsigned int page_size, enum table_type table_type){
    int idx;

    if(table_type == REG){
        idx = (tp[v_page_idx].address / page_size);
    } else {
        idx = find_mem_page_idx_inv(v_page_idx, tbl_page_c, tp, page_size);
    }

    for(int i = 0; i < mem_page_c; i++){
        if(lru_l[idx] < lru_l[i]) lru_l[i] -= 1;
    }
    lru_l[idx] = mem_page_c - 1;
}

static int wsclock_find_page_idx(unsigned int v_page_idx, unsigned int *wsc_hand, unsigned long *wsc_time, unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int mem_page_c, unsigned long *wsc_l, unsigned int page_size, enum table_type table_type){
    int idx = -1;
    for(int i = 0; i < tbl_page_c * 2; i++){
        if(tp[*wsc_hand].present != 0){
            if(tp[*wsc_hand].reference_bit != 0){
                tp[*wsc_hand].reference_bit = 0;
            } else {
                if(*wsc_time - (unsigned long)(mem_page_c/2) >= wsc_l[*wsc_hand]){
                    idx = (int)*wsc_hand;
                    break;
                }
            }
        }
        (*wsc_hand)++;
        (*wsc_hand) = (*wsc_hand) % tbl_page_c;
    }

    if(table_type == REG){
        wsc_l[v_page_idx] = *wsc_time;
    } else {
        wsc_l[idx] = *wsc_time;
    }

    (*wsc_time)++;
    (*wsc_hand)++;
    (*wsc_hand) = (*wsc_hand) % tbl_page_c;

    if(table_type == REG){
        return idx;
    } else {
        return (int)(tp[idx].address / page_size);
    }
}

static int second_chanse_find_page_idx(unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int mem_page_c, unsigned short *sc_l, unsigned int page_size, enum table_type table_type){
    int idx = -1;

    for(int i = 0; i < mem_page_c; i++){
        if(sc_l[i] != 0){
            sc_l[i] = 0;
        } else {
            idx = i;
        }
    }
    if(idx == -1)idx = 0;
    
    if(table_type == REG){
        return find_v_page_idx_reg(idx, tbl_page_c, tp, page_size);
    } else {
        return (tp[idx].address / page_size);
    }
}

static int fifo_find_page_idx(queue_t *queue, unsigned int v_page_idx){
    enqueue(queue, v_page_idx);
    return dequeue(queue);
}

static int nru_find_page_idx(unsigned int tbl_page_c, struct tbl_ent *tp, unsigned int page_size, enum table_type table_type){
    int idx = -1;
    short idx_class = 4;

    for(int i = 0; i < tbl_page_c; i++){
        if(tp[i].present != 0){
            if(tp[i].modified_bit == 0 && tp[i].reference_bit == 0 && idx_class > 0){
                idx = i;
                break;
            } else if(tp[i].modified_bit == 0 && tp[i].reference_bit == 1 && idx_class > 1){
                idx = i;
                idx_class = 1;
            } else if(tp[i].modified_bit == 1 && tp[i].reference_bit == 0 && idx_class > 2){
                idx = i;
                idx_class = 2;
            } else if(tp[i].modified_bit == 1 && tp[i].reference_bit == 1 && idx_class > 3){
                idx = i;
                idx_class = 3;
            }
        }
    }
    
    if(table_type == REG){
        return idx;
    } else {
        return (tp[idx].address / page_size);
    }
}

int get(unsigned int index, char *tName){
    if(index >= 0 && index < (vm.page_size * (vm.mem_page_c + vm.f_page_c))){
        unsigned int v_page_index = index / vm.page_size;
        unsigned int offset = index % vm.page_size;

             if(strcmp(tName, TNAME_FILL  ) == 0) vm.stat_read[0] += 1;
        else if(strcmp(tName, TNAME_BUBBLE) == 0) vm.stat_read[1] += 1;
        else if(strcmp(tName, TNAME_QUICK ) == 0) vm.stat_read[2] += 1;
        else if(strcmp(tName, TNAME_MERGE ) == 0) vm.stat_read[3] += 1;
        else if(strcmp(tName, TNAME_LINEAR) == 0) vm.stat_read[4] += 1;
        else if(strcmp(tName, TNAME_BINARY) == 0) vm.stat_read[5] += 1;

        unsigned int access = 0;
        for(int i = 0; i < 6; i++){
            access += vm.stat_read[i];
            access += vm.stat_write[i];
        }
        if(access % vm.table_print_intrvl == 0){
            printf("**** Table *************\n");
            for(int i = 0; i < vm.tbl_page_c; i++){
                printf("Index: %d\n", i);
                printf("Address: %d\n", vm.tp[i].address);
                printf("Refrence Bit: %d\n", vm.tp[i].reference_bit);
                printf("Modified Bit: %d\n", vm.tp[i].modified_bit);
                printf("Present Bit: %d\n\n", vm.tp[i].present);
            }
            printf("************************\n");
        }

        if(vm.table_type == INV){
            if(is_present_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size) == 0){
                if(strcmp(tName, TNAME_FILL) == 0) {
                    vm.stat_page_miss[0] += 1;
                    vm.stat_page_replacement[0] += 1;
                    vm.stat_disk_page_read[0] += 1;
                } else if(strcmp(tName, TNAME_BUBBLE) == 0) {
                    vm.stat_page_miss[1] += 1;
                    vm.stat_page_replacement[1] += 1;
                    vm.stat_disk_page_read[1] += 1;
                } else if(strcmp(tName, TNAME_QUICK) == 0) {
                    vm.stat_page_miss[2] += 1;
                    vm.stat_page_replacement[2] += 1;
                    vm.stat_disk_page_read[2] += 1;
                } else if(strcmp(tName, TNAME_MERGE) == 0) {
                    vm.stat_page_miss[3] += 1;
                    vm.stat_page_replacement[3] += 1;
                    vm.stat_disk_page_read[3] += 1;
                } else if(strcmp(tName, TNAME_LINEAR) == 0) {
                    vm.stat_page_miss[4] += 1;
                    vm.stat_page_replacement[4] += 1;
                    vm.stat_disk_page_read[4] += 1;
                } else if(strcmp(tName, TNAME_BINARY) == 0) {
                    vm.stat_page_miss[5] += 1;
                    vm.stat_page_replacement[5] += 1;
                    vm.stat_disk_page_read[5] += 1;
                }

                int v_page_idx_mem;
                if(vm.table_rep_alg == NRU) {
                    v_page_idx_mem = nru_find_page_idx(vm.tbl_page_c, vm.tp, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == FIFO) {
                    v_page_idx_mem = fifo_find_page_idx(vm.fifo_q, v_page_index);
                } else if(vm.table_rep_alg == SC) {
                    v_page_idx_mem = second_chanse_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.sc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == WSC) {
                    v_page_idx_mem = wsclock_find_page_idx(v_page_index, &(vm.wsc_hand), &(vm.wsc_time), vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.wsc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == LRU){
                    v_page_idx_mem = lru_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                swap_page_inv(v_page_idx_mem, v_page_index, &vm);
                int pg_idx = find_mem_page_idx_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size);
                return vm.mp[pg_idx * vm.page_size + offset];
            } else {
                int pg_idx = find_mem_page_idx_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size);
                if(vm.table_rep_alg == NRU){
                    vm.tp[pg_idx].reference_bit = 1;
                } else if(vm.table_rep_alg == SC){
                    vm.sc_l[pg_idx] = 1;
                } else if(vm.table_rep_alg == WSC){
                    vm.tp[pg_idx].reference_bit = 1;
                } else if(vm.table_rep_alg == LRU){
                    lru_update_page_idx(v_page_index, vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                return vm.mp[pg_idx * vm.page_size + offset];
            }
        } else {
            if(is_present_reg(v_page_index, vm.tbl_page_c, vm.tp) == 0){
                if(strcmp(tName, TNAME_FILL) == 0) {
                    vm.stat_page_miss[0] += 1;
                    vm.stat_page_replacement[0] += 1;
                    vm.stat_disk_page_read[0] += 1;
                } else if(strcmp(tName, TNAME_BUBBLE) == 0) {
                    vm.stat_page_miss[1] += 1;
                    vm.stat_page_replacement[1] += 1;
                    vm.stat_disk_page_read[1] += 1;
                } else if(strcmp(tName, TNAME_QUICK) == 0) {
                    vm.stat_page_miss[2] += 1;
                    vm.stat_page_replacement[2] += 1;
                    vm.stat_disk_page_read[2] += 1;
                } else if(strcmp(tName, TNAME_MERGE) == 0) {
                    vm.stat_page_miss[3] += 1;
                    vm.stat_page_replacement[3] += 1;
                    vm.stat_disk_page_read[3] += 1;
                } else if(strcmp(tName, TNAME_LINEAR) == 0) {
                    vm.stat_page_miss[4] += 1;
                    vm.stat_page_replacement[4] += 1;
                    vm.stat_disk_page_read[4] += 1;
                } else if(strcmp(tName, TNAME_BINARY) == 0) {
                    vm.stat_page_miss[5] += 1;
                    vm.stat_page_replacement[5] += 1;
                    vm.stat_disk_page_read[5] += 1;
                }

                int v_page_idx_mem;
                if(vm.table_rep_alg == NRU) {
                    v_page_idx_mem = nru_find_page_idx(vm.tbl_page_c, vm.tp, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == FIFO) {
                    v_page_idx_mem = fifo_find_page_idx(vm.fifo_q, v_page_index);
                } else if(vm.table_rep_alg == SC) {
                    v_page_idx_mem = second_chanse_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.sc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == WSC) {
                    v_page_idx_mem = wsclock_find_page_idx(v_page_index, &(vm.wsc_hand), &(vm.wsc_time), vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.wsc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == LRU){
                    v_page_idx_mem = lru_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                swap_page_reg(v_page_idx_mem, v_page_index, &vm);
                return vm.mp[vm.tp[v_page_index].address + offset];
            } else {
                if(vm.table_rep_alg == NRU){
                    vm.tp[v_page_index].reference_bit = 1;
                } else if(vm.table_rep_alg == SC){
                    vm.sc_l[vm.tp[v_page_index].address / vm.page_size] = 1;
                } else if(vm.table_rep_alg == WSC){
                    vm.tp[v_page_index].reference_bit = 1;
                } else if(vm.table_rep_alg == LRU){
                    lru_update_page_idx(v_page_index, vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                return vm.mp[vm.tp[v_page_index].address + offset];
            }
        }
    } else {
        return -1;
    }
}

void set(unsigned int index, int value, char *tName){
    if(index >= 0 && index < (vm.page_size * (vm.mem_page_c + vm.f_page_c))){
        unsigned int v_page_index = index / vm.page_size;
        unsigned int offset = index % vm.page_size;

             if(strcmp(tName, TNAME_FILL  ) == 0) vm.stat_write[0] += 1;
        else if(strcmp(tName, TNAME_BUBBLE) == 0) vm.stat_write[1] += 1;
        else if(strcmp(tName, TNAME_QUICK ) == 0) vm.stat_write[2] += 1;
        else if(strcmp(tName, TNAME_MERGE ) == 0) vm.stat_write[3] += 1;
        else if(strcmp(tName, TNAME_LINEAR) == 0) vm.stat_write[4] += 1;
        else if(strcmp(tName, TNAME_BINARY) == 0) vm.stat_write[5] += 1;

        unsigned int access = 0;
        for(int i = 0; i < 6; i++){
            access += vm.stat_read[i];
            access += vm.stat_write[i];
        }
        if(access % vm.table_print_intrvl == 0){
            printf("**** Table *************\n");
            for(int i = 0; i < vm.tbl_page_c; i++){
                printf("Index: %d\n", i);
                printf("Address: %d\n", vm.tp[i].address);
                printf("Refrence Bit: %d\n", vm.tp[i].reference_bit);
                printf("Modified Bit: %d\n", vm.tp[i].modified_bit);
                printf("Present Bit: %d\n", vm.tp[i].present);
            }
            printf("************************\n");
        }
        
        if(vm.table_type == INV){
            if(is_present_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size) == 0){
                if(strcmp(tName, TNAME_FILL) == 0) {
                    vm.stat_page_miss[0] += 1;
                    vm.stat_page_replacement[0] += 1;
                    vm.stat_disk_page_write[0] += 1;
                } else if(strcmp(tName, TNAME_BUBBLE) == 0) {
                    vm.stat_page_miss[1] += 1;
                    vm.stat_page_replacement[1] += 1;
                    vm.stat_disk_page_write[1] += 1;
                } else if(strcmp(tName, TNAME_QUICK) == 0) {
                    vm.stat_page_miss[2] += 1;
                    vm.stat_page_replacement[2] += 1;
                    vm.stat_disk_page_write[2] += 1;
                } else if(strcmp(tName, TNAME_MERGE) == 0) {
                    vm.stat_page_miss[3] += 1;
                    vm.stat_page_replacement[3] += 1;
                    vm.stat_disk_page_write[3] += 1;
                } else if(strcmp(tName, TNAME_LINEAR) == 0) {
                    vm.stat_page_miss[4] += 1;
                    vm.stat_page_replacement[4] += 1;
                    vm.stat_disk_page_write[4] += 1;
                } else if(strcmp(tName, TNAME_BINARY) == 0) {
                    vm.stat_page_miss[5] += 1;
                    vm.stat_page_replacement[5] += 1;
                    vm.stat_disk_page_write[5] += 1;
                }

                int v_page_idx_mem;
                if(vm.table_rep_alg == NRU) {
                    v_page_idx_mem = nru_find_page_idx(vm.tbl_page_c, vm.tp, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == FIFO) {
                    v_page_idx_mem = fifo_find_page_idx(vm.fifo_q, v_page_index);
                } else if(vm.table_rep_alg == SC) {
                    v_page_idx_mem = second_chanse_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.sc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == WSC) {
                    v_page_idx_mem = wsclock_find_page_idx(v_page_index, &(vm.wsc_hand), &(vm.wsc_time), vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.wsc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == LRU){
                    v_page_idx_mem = lru_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                swap_page_inv(v_page_idx_mem, v_page_index, &vm);
                int pg_idx = find_mem_page_idx_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size);
                vm.mp[pg_idx * vm.page_size + offset] = value;
            } else {
                int pg_idx = find_mem_page_idx_inv(v_page_index, vm.tbl_page_c, vm.tp, vm.page_size);
                if(vm.table_rep_alg == NRU){
                    vm.tp[pg_idx].reference_bit = 1;
                    vm.tp[pg_idx].modified_bit = 1;
                } else if(vm.table_rep_alg == SC){
                    vm.sc_l[pg_idx] = 1;
                } else if(vm.table_rep_alg == WSC){
                    vm.tp[pg_idx].reference_bit = 1;
                } else if(vm.table_rep_alg == LRU){
                    lru_update_page_idx(v_page_index, vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                vm.mp[pg_idx * vm.page_size + offset] = value;
            }
        } else {
            if(is_present_reg(v_page_index, vm.tbl_page_c, vm.tp) == 0){
                if(strcmp(tName, TNAME_FILL) == 0) {
                    vm.stat_page_miss[0] += 1;
                    vm.stat_page_replacement[0] += 1;
                    vm.stat_disk_page_write[0] += 1;
                } else if(strcmp(tName, TNAME_BUBBLE) == 0) {
                    vm.stat_page_miss[1] += 1;
                    vm.stat_page_replacement[1] += 1;
                    vm.stat_disk_page_write[1] += 1;
                } else if(strcmp(tName, TNAME_QUICK) == 0) {
                    vm.stat_page_miss[2] += 1;
                    vm.stat_page_replacement[2] += 1;
                    vm.stat_disk_page_write[2] += 1;
                } else if(strcmp(tName, TNAME_MERGE) == 0) {
                    vm.stat_page_miss[3] += 1;
                    vm.stat_page_replacement[3] += 1;
                    vm.stat_disk_page_write[3] += 1;
                } else if(strcmp(tName, TNAME_LINEAR) == 0) {
                    vm.stat_page_miss[4] += 1;
                    vm.stat_page_replacement[4] += 1;
                    vm.stat_disk_page_write[4] += 1;
                } else if(strcmp(tName, TNAME_BINARY) == 0) {
                    vm.stat_page_miss[5] += 1;
                    vm.stat_page_replacement[5] += 1;
                    vm.stat_disk_page_write[5] += 1;
                }

                int v_page_idx_mem;
                if(vm.table_rep_alg == NRU) {
                    v_page_idx_mem = nru_find_page_idx(vm.tbl_page_c, vm.tp, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == FIFO) {
                    v_page_idx_mem = fifo_find_page_idx(vm.fifo_q, v_page_index);
                } else if(vm.table_rep_alg == SC) {
                    v_page_idx_mem = second_chanse_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.sc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == WSC) {
                    v_page_idx_mem = wsclock_find_page_idx(v_page_index, &(vm.wsc_hand), &(vm.wsc_time), vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.wsc_l, vm.page_size, vm.table_type);
                } else if(vm.table_rep_alg == LRU){
                    v_page_idx_mem = lru_find_page_idx(vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                swap_page_reg(v_page_idx_mem, v_page_index, &vm);
                vm.mp[vm.tp[v_page_index].address + offset] = value;
            } else {
                if(vm.table_rep_alg == NRU){
                    vm.tp[v_page_index].reference_bit = 1;
                    vm.tp[v_page_index].modified_bit = 1;
                } else if(vm.table_rep_alg == SC){
                    vm.sc_l[vm.tp[v_page_index].address / vm.page_size] = 1;
                } else if(vm.table_rep_alg == WSC){
                    vm.tp[v_page_index].reference_bit = 1;
                } else if(vm.table_rep_alg == LRU){
                    lru_update_page_idx(v_page_index, vm.tbl_page_c, vm.tp, vm.mem_page_c, vm.lru_l, vm.page_size, vm.table_type);
                }
                vm.mp[vm.tp[v_page_index].address + offset] = value;
            }
        }
    }
}

void print_stats(){
    unsigned long tot_read = 0;
    unsigned long tot_write = 0;
    unsigned long tot_page_miss= 0;
    unsigned long tot_page_replacement = 0;
    unsigned long tot_disk_page_read = 0;
    unsigned long tot_disk_page_write = 0;

    for(int i = 0; i < 6; i++){
             if(i == 0)printf("\n**** Fill **************\n");
        else if(i == 1)printf("\n**** Bubble Sort *******\n");
        else if(i == 2)printf("\n**** Quick Sort ********\n");
        else if(i == 3)printf("\n**** Merge *************\n");
        else if(i == 4)printf("\n**** Linear Search *****\n");
        else if(i == 5)printf("\n**** Binary Search *****\n");

        tot_read += vm.stat_read[i];
        tot_write += vm.stat_write[i];
        tot_page_miss += vm.stat_page_miss[i];
        tot_page_replacement += vm.stat_page_replacement[i];
        tot_disk_page_read += vm.stat_disk_page_read[i];
        tot_disk_page_write += vm.stat_disk_page_write[i];

        printf("Reads: %ld\n", vm.stat_read[i]);
        printf("Writes: %ld\n", vm.stat_write[i]);
        printf("Page Miss: %ld\n", vm.stat_page_miss[i]);
        printf("Page Replacement: %ld\n", vm.stat_page_replacement[i]);
        printf("Disk Page Reads: %ld\n", vm.stat_disk_page_read[i]);
        printf("Disk Page Writes: %ld\n", vm.stat_disk_page_write[i]);
        
        for(int j = 0; j < 24;j++)printf("*");
        printf("\n");
    }
    printf("\n**** TOTAL *************\n");
    printf("Reads: %ld\n", tot_read);
    printf("Writes: %ld\n", tot_write);
    printf("Page Miss: %ld\n", tot_page_miss);
    printf("Page Replacement: %ld\n", tot_page_replacement);
    printf("Disk Page Reads: %ld\n", tot_disk_page_read);
    printf("Disk Page Writes: %ld\n", tot_disk_page_write);
    for(int j = 0; j < 24;j++)printf("*");
    printf("\n");
}
