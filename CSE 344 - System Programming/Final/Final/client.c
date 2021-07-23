#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define FPATH_LENGTH 256

void read_parameters(int argc, char **argv, unsigned int *pr_id, char *ip, unsigned int *port, char *filepath){
    short param_i = 0;
    short param_a = 0;
    short param_p = 0;
    short param_o = 0;
    
    int opt;
    while((opt = getopt(argc, argv, ":i:a:p:o:")) != -1){
        switch(opt){
            case 'i':
                if(optarg != NULL && strlen(optarg) > 0){
                    for(int i = 0; i < strlen(optarg); i++){
                        if(!isdigit(optarg[i])){
                            fprintf(stderr, "Error: Process id should be a positive integer value.\n");
                            fprintf(stderr, "Program will be terminated...\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                    param_i = 1;
                    *pr_id = atoi(optarg);
                    if(*pr_id < 1){
                        fprintf(stderr, "Error: Process id must be greater than 0.\n");
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -l.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'a':
                if(optarg != NULL && strlen(optarg) > 0){
                    if(strlen(optarg) < 16){
                        param_a = 1;
                        strcpy(ip, optarg);
                    } else {
                        fprintf(stderr, "Error: Argument -a must be less than %d characters.\n", 16);
                        fprintf(stderr, "Program will be terminated...\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Error: Invalid argument -o.\n");
                    fprintf(stderr, "Program will be terminated...\n");
                    exit(EXIT_FAILURE);
                }
                break;
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
                        strcpy(filepath, optarg);
                    } else {
                        fprintf(stderr, "Error: Argument -o must be less than %d characters.\n", FPATH_LENGTH);
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

    if(!param_i){
        fprintf(stderr, "Error: Command line argument -i must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_a){
        fprintf(stderr, "Error: Command line argument -a must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_p){
        fprintf(stderr, "Error: Command line argument -p must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
    if(!param_o){
        fprintf(stderr, "Error: Command line argument -o must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    }
}

void shift_left_str(char *str, int amount){
    for(int i = amount; i < strlen(str)+1; i++){
        str[i - amount] = str[i];
    }
}

int main(int argc, char **argv){
    unsigned int pr_id;
    char ip[16];
    unsigned int port;
    char filepath[FPATH_LENGTH];

    read_parameters(argc, argv, &pr_id, ip, &port, filepath);
    printf("%s\n", ip);
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0){
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }

    FILE *fp = fopen(filepath, "r");
    char str[2048];
    char str2[2048];
    while(fgets(str, 2048, fp) != NULL){
        str[strcspn(str, "\r\n")] = '\0';
        strcpy(str2, str);
        char *tkn = strtok(str2, " ");
        int id = atoi(tkn);
        if(pr_id == id){
            shift_left_str(str, strlen(tkn));
            send(sock,str ,strlen(str), 0);
            read(sock ,str, 2048);
            printf("%s\nNEW\n", str);
        }
    }
    fclose(fp);
    return 0;
}