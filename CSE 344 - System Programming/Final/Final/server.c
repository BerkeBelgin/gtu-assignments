#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "database.h"

#define FPATH_LENGTH 256

unsigned short exit_sig;

void exit_signal(){
    exit_sig = 1;
    exit(EXIT_SUCCESS);
}

void free_resources(FILE *fp_log, FILE *fp_ds){
    if(fp_log != NULL)fclose(fp_log);
    if(fp_ds != NULL)fclose(fp_ds);
}

void read_parameters(int argc, char **argv, unsigned int *port, char *log_file_path, unsigned int *pool_size, char *dataset_path){
    short param_p = 0;
    short param_o = 0;
    short param_l = 0;
    short param_d = 0;
    
    int opt;
    while((opt = getopt(argc, argv, ":p:o:l:d:")) != -1){
        switch(opt){
            case 'p':
                if(optarg != NULL && strlen(optarg) > 0){
                    for(int i = 0; i < strlen(optarg); i++){
                        if(!isdigit(optarg[i])){
                            fprintf(stderr, "Error: Port number should be a positive integer value.\n");
                            fprintf(stderr, "Program will be terminated...\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    param_p = 1;
                    *port = atoi(optarg);
                    if(*port < 1001 || *port > 49151){
                        fprintf(stderr, "Error: Port number must be between 1001 and 49151.\n");
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -p.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'o':
                if(optarg != NULL && strlen(optarg) > 0){
                    if(strlen(optarg) < FPATH_LENGTH){
                        param_o = 1;
                        strcpy(log_file_path, optarg);
                    } else {
                        fprintf(stderr, "Error: Argument -o must be less than %d characters.\n", FPATH_LENGTH);
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -o.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'l':
                if(optarg != NULL && strlen(optarg) > 0){
                    for(int i = 0; i < strlen(optarg); i++){
                        if(!isdigit(optarg[i])){
                            fprintf(stderr, "Error: Pool size should be a positive integer value.\n");
                            fprintf(stderr, "Program will be terminated...\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    param_l = 1;
                    *pool_size = atoi(optarg);
                    if(*pool_size < 2){
                        fprintf(stderr, "Error: Pool size must be greater than 1.\n");
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -l.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd':
                if(optarg != NULL && strlen(optarg) > 0){
                    if(strlen(optarg) < FPATH_LENGTH){
                        param_d = 1;
                        strcpy(dataset_path, optarg);
                    } else {
                        fprintf(stderr, "Error: Argument -d must be less than %d characters.\n", FPATH_LENGTH);
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -d.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case ':': 
                fprintf(stderr, "Warning: %c parameter did not get any value. It will be ignored.\n", opt); 
                break; 
            case '?': 
                fprintf(stderr, "Warning: %c parameter could not be recognised. It will be ignored.\n", optopt);
                break; 
        }
    }

    while(optind < argc){
        fprintf(stderr, "Warning: %s value does not belong to any parameter. It will be ignored.\n", argv[optind]);
        optind++;
    }

    if(!param_p){
        fprintf(stderr, "Error: Command line argument -p must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_l){
        fprintf(stderr, "Error: Command line argument -o must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_o){
        fprintf(stderr, "Error: Command line argument -l must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_d){
        fprintf(stderr, "Error: Command line argument -d must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
}

int get_colc_dataset(FILE *fp){
    char line[2048];
    if(fgets(line, 2048, fp) == NULL) return -1;

    int res = 0;
    char *tkn = strtok(line, ",");
    while(tkn != NULL){
        res++;
        tkn = strtok(NULL, ",");
    }
    fseek(fp, 0, SEEK_SET);
    return res;
}

void load_dataset(FILE *fp, dbm_t *dbmo, int col_size){
    char line[2048];
    char line2[2048];
    
    memset(line, '\0', 2048);
    while(fgets(line, 2048, fp) != NULL){
        line[strcspn(line, "\r\n")] = '\0';
        if(line[strlen(line)-1] == ',')line[strlen(line)-1] = '\0';
        
        memset(line2, '\0', 2048);
        char *tkn = strtok(line, " ");
        while(tkn != NULL){
            strcat(line2, tkn);
            tkn = strtok(NULL, " ");
        }

        int t_idx;
        do {
            t_idx = -1;
            for(int i = 1; i < strlen(line2); i++){
                if(line2[i-1] == ',' && line2[i] == ','){
                    t_idx = i;
                }
            }
            if(t_idx != -1){
                for(int i = strlen(line2); i > t_idx; i--){
                    line2[i] = line2[i-1];
                }
                line2[t_idx] = ' ';
            }
        }while(t_idx != -1);
        
        if((tkn = strtok(line2, ",")) != NULL){
            char *strv[col_size];
            for(int i = 0; i < col_size; i++){
                if(tkn != NULL){
                    strv[i] = (char *) malloc(sizeof(char) * (strlen(tkn)+1));
                    memset(strv[i], '\0', strlen(tkn)+1);
                    strcpy(strv[i], tkn);
                    tkn = strtok(NULL, ",");
                } else {
                    strv[i] = (char *) malloc(sizeof(char) * 2);
                    strcpy(strv[i], " ");
                }
            }
            insert(dbmo, strv);
            for(int i = 0; i < col_size; i++){
                free(strv[i]);
            }
        }
    }
}

int main(int argc, char **argv){
    unsigned int port;
    char logfile_path[FPATH_LENGTH];
    unsigned int pool_size;
    char dataset_path[FPATH_LENGTH];

    exit_sig = 0;
    signal(SIGINT, exit_signal);

    read_parameters(argc, argv, &port, logfile_path, &pool_size, dataset_path);

    FILE *fp_log = NULL;
    FILE *fp_ds = NULL;

    if((fp_log = fopen(logfile_path, "a")) == NULL){
        fprintf(stderr, "Could not open/create file %s.\nProgram will be terminated...\n", logfile_path);
        free_resources(fp_log, fp_ds);
        exit(EXIT_FAILURE);
    }
    if((fp_ds = fopen(dataset_path, "r")) == NULL){
        fprintf(stderr, "Could not open/create file %s.\nProgram will be terminated...\n", dataset_path);
        free_resources(fp_log, fp_ds);
        exit(EXIT_FAILURE);
    }
    int col_size = get_colc_dataset(fp_ds);
    dbm_t dbmo;
    init_dbm(&dbmo, col_size);
    load_dataset(fp_ds, &dbmo, col_size);
    
    // char *ptr = exec_query(&dbmo, "SELECT     Series_reference    FROM    TABLE   ;   ");
    // printf("\n%s", ptr);
    // free_query_resp(ptr);
    // ptr = exec_query(&dbmo, "UPDATE  TABLE  SET col2='MERABA' WHERE col1='abcd'   ;   ");
    // printf("\n%s\n", ptr);
    // free_query_resp(ptr);
    
    
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    char buff[2048];
    char *response;
    while(1){
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }

        read(new_socket , buff, 2048);
        response = exec_query(&dbmo, buff);
        send(new_socket , response , strlen(response) , 0);
        free_query_resp(response);
    }

    destroy_dbm(&dbmo);
    free_resources(fp_log, fp_ds);
    exit(EXIT_SUCCESS);
}