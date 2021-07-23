#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fat12_fs.h"

void read_params(int argc, char *argv[], unsigned int *block_size, char *filename){
    if(argc == 3){
        for(int i = 0; i < strlen(argv[1]); i++){
            if(!isdigit(argv[1][i])){
                fprintf(stderr, "Error: Block Size must be a positive number.\n");
                fprintf(stderr, "Program will be terminated...\n");
                exit(EXIT_FAILURE);
            }
        }
        *block_size = atoi(argv[1]);
        if(strlen(argv[2]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Filename must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(filename, argv[2]);
    } else {
        fprintf(stderr, "Error: Block Size and File Name must be given as parameters respectively.\n");
        fprintf(stderr, "Program will be terminated...\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    unsigned int block_size;
    char filename[MAX_LEN_FNAME];

    read_params(argc, argv, &block_size, filename);

    fat12_fs_t fsp;

    create_fat12_fs(&fsp, block_size, filename);
    close_fat12_fs(&fsp);
    return 0;
}