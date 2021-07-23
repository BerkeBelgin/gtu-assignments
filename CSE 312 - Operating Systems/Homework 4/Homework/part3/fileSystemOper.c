#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "fat12_fs.h"

#define MAX_LEN_FNAME 128

#define OP_DIR "dir"
#define OP_MKDIR "mkdir"
#define OP_RMDIR "rmdir"
#define OP_DUMPE2FS "dumpe2fs"
#define OP_WRITE "write"
#define OP_READ "read"
#define OP_DEL "del"

#define OP_DIR_NUM 0
#define OP_MKDIR_NUM 1
#define OP_RMDIR_NUM 2
#define OP_DUMPE2FS_NUM 3
#define OP_WRITE_NUM 4
#define OP_READ_NUM 5
#define OP_DEL_NUM 6

void trim_quotes(char *str){
    if(str[0] == '"' && str[strlen(str)-1] == '"'){
        for(int i = 1; i < (strlen(str)-1); i++){
            str[i-1] = str[i];
        }
        str[strlen(str)-1] = '\0';
    }
}

void read_params(int argc, char *argv[], char *filename, short *op, char *op_path, char *filename2){
    if(argc < 3){
        fprintf(stderr, "Error: Incorrect parameters.\n");
        fprintf(stderr, "Program will be terminated...\n");
        exit(EXIT_FAILURE);
    }

    if(strlen(argv[1]) > (MAX_LEN_FNAME - 1)){
        fprintf(stderr, "Error: Filename must be less than %d characters.\n", MAX_LEN_FNAME);
        fprintf(stderr, "Program will be terminated...\n");
        exit(EXIT_FAILURE);
    }
    strcpy(filename, argv[1]);

    if(strcmp(argv[2], OP_DIR) == 0){
        *op = OP_DIR_NUM;
        
        if(argc != 4){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);
    } else if(strcmp(argv[2], OP_MKDIR) == 0){
        *op = OP_MKDIR_NUM;

        if(argc != 4){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);
    } else if(strcmp(argv[2], OP_RMDIR) == 0){
        *op = OP_RMDIR_NUM;

        if(argc != 4){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);
    } else if(strcmp(argv[2], OP_DUMPE2FS) == 0){
        *op = OP_DUMPE2FS_NUM;

        if(argc != 3){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
    } else if(strcmp(argv[2], OP_WRITE) == 0){
        *op = OP_WRITE_NUM;

        if(argc != 5){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);

        if(strlen(argv[4]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(filename2, argv[4]);
    } else if(strcmp(argv[2], OP_READ) == 0){
        *op = OP_READ_NUM;

        if(argc != 5){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);

        if(strlen(argv[4]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(filename2, argv[4]);
    } else if(strcmp(argv[2], OP_DEL) == 0){
        *op = OP_DEL_NUM;

        if(argc != 4){
            fprintf(stderr, "Error: Incorrect parameters.\n");
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }

        if(strlen(argv[3]) > (MAX_LEN_FNAME - 1)){
            fprintf(stderr, "Error: Path must be less than %d characters.\n", MAX_LEN_FNAME);
            fprintf(stderr, "Program will be terminated...\n");
            exit(EXIT_FAILURE);
        }
        strcpy(op_path, argv[3]);
        trim_quotes(op_path);
    } else {
        fprintf(stderr, "Error: Operation %s is unknown.\n", argv[2]);
        fprintf(stderr, "Program will be terminated...\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){
    char filename[MAX_LEN_FNAME];
    short op;
    char op_path[MAX_LEN_FNAME];
    char filename2[MAX_LEN_FNAME];

    read_params(argc, argv, filename, &op, op_path, filename2);
    
    fat12_fs_t fsp;

    if(open_fat12_fs(&fsp, filename) == -1)printf("%s HERE2\n", strerror(errno));

    switch(op){
        case OP_DIR_NUM:
            dir(&fsp, op_path);
            break;
        case OP_MKDIR_NUM:
            mkdir(&fsp, op_path);
            break;
        case OP_RMDIR_NUM:
            rmdir(&fsp, op_path);
            break;
        case OP_DUMPE2FS_NUM:
            dumpe2fs(&fsp);
            break;
        case OP_WRITE_NUM:
            write(&fsp, op_path, filename2);
            break;
        case OP_READ_NUM:
            read(&fsp, op_path, filename2);
            break;
        case OP_DEL_NUM:
            del(&fsp, op_path);
            break;
    }

    close_fat12_fs(&fsp);

    return 0;
}