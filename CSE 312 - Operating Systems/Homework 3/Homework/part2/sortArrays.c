#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

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

int linear_search(int left, int right, int num, char *tName){
    for(int i = left; i < right; i++){
        if(get(i, tName) == num)return i;
    }
    return -1;
}

int binary_search(int left, int right, int num, char *tName){
    if(left <= right){
        int mid = (left + right) / 2;
        int t_num = get(mid, tName);
        if(t_num == num)return mid;
        else if(t_num > num)return binary_search(left, mid - 1, num, tName);
        else return binary_search(mid + 1, right, num, tName);

    } else {
        return -1;
    }
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

void read_params(int argc, char *args[], int *frame_size, int *numPhysical, int *numVirtual, int *pageTablePrint){
    if(argc < 8){
        fprintf(stderr, "Insufficient commandline arguments.\nCommandline arguments should have these arguments respectively:\n");
        fprintf(stderr, "./out_file\nframe_size\nphysical_frame_amount\nvirtual_frame_amount\npage_rep_algorithm\ntable_type\npage_table_print_interval\nfilename\n");
        fprintf(stderr, "Program will be terminated...\n");
        exit(EXIT_FAILURE);
    } else {
        for(int i = 0; i < strlen(args[1]); i++){
            if(!isdigit(args[1][i])){
                fprintf(stderr, "Error: Frame size should be a positive integer value.\n");
                fprintf(stderr, "Program will be terminated...\n");
                exit(EXIT_FAILURE);
            }
        }
        *frame_size = atoi(args[1]);

        for(int i = 0; i < strlen(args[2]); i++){
            if(!isdigit(args[2][i])){
                fprintf(stderr, "Error: Physical Frame Amount should be a positive integer value.\n");
                fprintf(stderr, "Program will be terminated...\n");
                exit(EXIT_FAILURE);
            }
        }
        *numPhysical = atoi(args[2]);

        for(int i = 0; i < strlen(args[3]); i++){
            if(!isdigit(args[3][i])){
                fprintf(stderr, "Error: Virtual Frame Amount should be a positive integer value.\n");
                fprintf(stderr, "Program will be terminated...\n");
                exit(EXIT_FAILURE);
            }
        }
        *numVirtual = atoi(args[3]);

        if(strcmp(args[4], TREP_FIFO) != 0 
        && strcmp(args[4], TREP_LRU)  != 0 
        && strcmp(args[4], TREP_NRU)  != 0
        && strcmp(args[4], TREP_SC)   != 0
        && strcmp(args[4], TREP_WSC)  != 0){
            fprintf(stderr, "Error: Unknown Page replacement type. Valid types are \"FIFO\", \"LRU\", \"NRU\", \"SC\", \"WSClock\"\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strcmp(args[5], TTYPE_REGULAR)  != 0
        && strcmp(args[5], TTYPE_INVERTED) != 0){
            fprintf(stderr, "Error: Unknown Page table type. Valid types are \"regular\", \"inverted\"\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < strlen(args[6]); i++){
            if(!isdigit(args[6][i])){
                fprintf(stderr, "Error: Page table print interval should be a positive integer value.\n");
                fprintf(stderr, "Program will be terminated...\n");
                exit(EXIT_FAILURE);
            }
        }
        *pageTablePrint = atoi(args[6]);
    }
}

void *quicksort_thread(void *tmp_args){
    struct th_args *args = tmp_args;
    quickSort(args->n1, args->n2, TNAME_QUICK);
    return NULL;
}

void *bubblesort_thread(void *tmp_args){
    struct th_args *args = tmp_args;
    bubbleSort(args->n1, args->n2, TNAME_BUBBLE);
    return NULL;
}

void *linear_search_thread(void *tmp_args){
    struct th_args *args = tmp_args;
    linear_search(args->n1, args->n2, 182, TNAME_LINEAR);
    linear_search(args->n1, args->n2, 62, TNAME_LINEAR);
    linear_search(args->n1, args->n2, 496, TNAME_LINEAR);
    linear_search(args->n1, args->n2, -20, TNAME_LINEAR);
    linear_search(args->n1, args->n2, 3, TNAME_LINEAR);
    return NULL;
}

void *binary_search_thread(void *tmp_args){
    struct th_args *args = tmp_args;
    binary_search(args->n1, args->n2, 182, TNAME_BINARY);
    binary_search(args->n1, args->n2, 62, TNAME_BINARY);
    binary_search(args->n1, args->n2, 496, TNAME_BINARY);
    binary_search(args->n1, args->n2, -20, TNAME_BINARY);
    binary_search(args->n1, args->n2, 3, TNAME_BINARY);
    return NULL;
}

int main(int argc, char *args[]){
    int frame_size;
    int num_phy;
    int num_vir;
    int ptpi;

    srand(1000);

    read_params(argc, args, &frame_size, &num_phy, &num_vir, &ptpi);
    vir_mem_create(frame_size, num_phy, num_vir, args[4], args[5], ptpi, args[7]);

    int fr_size = h_pow(2, frame_size);
    int vir_size = h_pow(2, num_vir) * fr_size;

    // fill
    for(int i = 0; i < vir_size; i++){
        int num = rand() % vir_size;
        set(i, num, TNAME_FILL);
    }

    // sort
    pthread_t bs_t;
    pthread_t qs_t;

    struct th_args bs_t_args = {0, vir_size/2 - 1};
    struct th_args qs_t_args = {vir_size/2, vir_size - 1};

    pthread_create(&bs_t, NULL, bubblesort_thread, &bs_t_args);
    pthread_join(bs_t, NULL);
    pthread_create(&qs_t, NULL, quicksort_thread, &qs_t_args);
    pthread_join(qs_t, NULL);
    
    // merge
    bubbleSort(0, vir_size - 1, TNAME_MERGE);

    // search
    pthread_t lis_t;
    pthread_t bis_t;

    struct th_args lis_t_args = {0, vir_size};
    struct th_args bis_t_args = {0, vir_size - 1};

    pthread_create(&lis_t, NULL, linear_search_thread, &lis_t_args);
    pthread_join(lis_t, NULL);
    pthread_create(&bis_t, NULL, binary_search_thread, &bis_t_args);
    pthread_join(bis_t, NULL);

    for(int i = 0; i < vir_size; i++){
        printf("%-4d ", get(i, ""));
        if(i % fr_size == (fr_size - 1))printf("\n");
    }

    print_stats();
    vir_mem_destroy();

    return 0;
}
