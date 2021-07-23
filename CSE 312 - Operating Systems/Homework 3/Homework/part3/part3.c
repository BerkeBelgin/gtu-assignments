#include <stdio.h>
#include <stdlib.h>

#include "vmem.h"

struct vir_mem vm;

struct th_args {
    int n1;
    int n2;
};

void h_swap(int i, int j, char *tName){
    int tmp_i = get(i, tName);
    int tmp_j = get(j, tName);
    set(i, tmp_j, tName);
    set(j, tmp_i, tName);
}

void quickSort(int low, int high, char *tName){
    if(low < high){
        int pivot = get(high, tName);
        int i = (low - 1);

        for(int j = low; j <= high - 1; j++){
            if(get(j, tName) < pivot){
                i++;
                h_swap(i, j, tName);
            }
        }
        h_swap(i+1, high, tName);

        quickSort(low, i, tName);
        quickSort(i + 2, high, tName);
    }
}

void bubbleSort(int low, int high, char *tName){
    int swp;
    do {
        swp = 0;
        for(int i = low; i < high; i++){
            if(get(i, tName) > get(i+1, tName)){
                h_swap(i, i+1, tName);
                swp = 1;
            }
        }
    } while(swp);
}

int main(int argc, char *args[]){
    srand(1000);

    for(int i = 0; i <= 4; i++){
        unsigned int vir_size = h_pow(2, 7);
        vir_mem_create(i, 4 - i, 7 - i, TREP_LRU, TTYPE_REGULAR, __INT32_MAX__, "tempdisk");
        // fill
        for(int i = 0; i < vir_size; i++){
            int num = rand() % vir_size;
            set(i, num, TNAME_FILL);
        }

        bubbleSort(0, vir_size - 1, TNAME_BUBBLE);
        quickSort(0, vir_size - 1, TNAME_QUICK);
        
        printf("\nFOR FRAME SIZE = %d\n", h_pow(2, i));
        print_stats();
        vir_mem_destroy();
    }
    return 0;
}
