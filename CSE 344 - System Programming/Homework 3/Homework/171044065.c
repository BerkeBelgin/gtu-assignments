#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <sys/mman.h>
#include <semaphore.h>

void read_parameters(int argc, char **argv, int *has_porato_or_not, char *shared_memory_name, char *fifo_addresses_file_path, char *semaphore_name){
    int param_b = 0;
    int param_s = 0;
    int param_f = 0;
    int param_m = 0;

    int opt;
    while((opt = getopt(argc, argv, ":b:s:f:m:")) != -1){
        switch(opt){
            case 'b':
                if(optarg != NULL && strlen(optarg) > 0){
                    param_b = 1;
                    *has_porato_or_not = atoi(optarg);
                }
                break;
            case 's':
                if(optarg != NULL && strlen(optarg) > 0){
                    param_s = 1;
                    strcpy(shared_memory_name, optarg);
                }
                break;
            case 'f':
                if(optarg != NULL && strlen(optarg) > 0){
                    param_f = 1;
                    strcpy(fifo_addresses_file_path, optarg);
                }
                break;
            case 'm':
                if(optarg != NULL && strlen(optarg) > 0){
                    param_m = 1;
                    strcpy(semaphore_name, optarg);
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

    if(!param_b){
        fprintf(stderr, "Error: Command line argument -b must be provided.\nProgram will be terminated.\n");
        exit(0);
    }
    if(!param_s){
        fprintf(stderr, "Error: Command line argument -s must be provided.\nProgram will be terminated.\n");
        exit(0);
    }
    if(!param_f){
        fprintf(stderr, "Error: Command line argument -f must be provided.\nProgram will be terminated.\n");
        exit(0);
    }
    if(!param_m){
        fprintf(stderr, "Error: Command line argument -m must be provided.\nProgram will be terminated.\n");
        exit(0);
    }
}

void read_fifo_paths(int *fifo_pathsc, char ***fifo_paths, char *filepath){
    char tmp[256];

    FILE *fp = fopen(filepath, "r");
    
    *fifo_pathsc = 0;
    while(fgets(tmp, 256, fp) != NULL) (*fifo_pathsc) += 1;
    *fifo_paths = (char**) malloc((*fifo_pathsc) * sizeof(char*));

    rewind(fp);
    for(int i = 0; fgets(tmp, 256, fp) != NULL && i < *fifo_pathsc; i++){
        if(tmp[strlen(tmp)-1] == '\n')tmp[strlen(tmp)-1] = '\0';
        (*fifo_paths)[i] = (char*) malloc(strlen(tmp) * sizeof(char));
        strcpy((*fifo_paths)[i], tmp);
		mkfifo(str_fifo_local, S_IRUSR | S_IWUSR);
    }
    fclose(fp);
}

void free_fifo_paths(int fifo_pathsc, char **fifo_paths){
    for(int i = 0; i < fifo_pathsc; i++) free(fifo_paths[i]);
    free(fifo_paths);
}

void init_fifo_conns(int indx, int fifo_pathsc, char **fifo_paths, int *fifo_remotesc, char ***fifo_remotes, char **fifo_local){
    *fifo_remotesc = fifo_pathsc - 1;

    *fifo_remotes = (char**) malloc((*fifo_remotesc) * sizeof(char*));
    for(int i = 0, j = 0; i < fifo_pathsc; i++){
        if(i == indx){
            *fifo_local = (char*) malloc(strlen(fifo_paths[i]) * sizeof(char));
            strcpy(*fifo_local, fifo_paths[i]);
        } else {
            (*fifo_remotes)[j] = (char*) malloc(strlen(fifo_paths[i]) * sizeof(char));
            strcpy((*fifo_remotes)[j], fifo_paths[i]);
            j++;
        }
    }
}

void free_fifo_conns(int fifo_remotesc, char **fifo_remotes, char *fifo_local){
    for(int i = 0; i < fifo_remotesc; i++) free(fifo_remotes[i]);
    free(fifo_remotes);
    free(fifo_local);
}

void connect_fifos(int index, int fifo_remotesc, int *fifo_remotes, int *fifo_local, int str_fifo_remotesc, char **str_fifo_remotes, char *str_fifo_local){
    for(int i = 0, j = 0; i < fifo_remotesc+1; i++){
        if(i == index) {
            printf("Using fifo:     %s\n", str_fifo_local);
            *fifo_local = open(str_fifo_local, O_RDONLY);
        } else {
            printf("Connected fifo: %s\n", str_fifo_remotes[j]);
            fifo_remotes[j] = open(str_fifo_remotes[j], O_WRONLY);
            j++;
        }
    }
}

void disconnect_fifos(int index, int fifo_remotesc, int *fifo_remotes, int *fifo_local){
    for(int i = 0, j = 0; i < fifo_remotesc+1; i++){
        if(i == index) {
            close(*fifo_local);
        } else {
            close(fifo_remotes[i]);
            j++;
        }
    }
}

int fifo_wait(int fd, int *pid, int *indx){
    char msg1[16];
    char msg2[16];
    memset(msg1, '\0', 16);
    memset(msg2, '\0', 16);

    char c;
    while(read(fd, &c, 1) > 0){
        if(c == '-') break;
        strncat(msg1, &c, 1);
    }
    while(read(fd, &c, 1) > 0){
        if(c == ',') break;
        strncat(msg2, &c, 1);
    }

    int i_msg1 = atoi(msg1);
    int i_msg2 = atoi(msg2);
    if(i_msg2 != 0){
        *indx = i_msg1;
        *pid = i_msg2;
        return 1;
    } else if(strcmp(msg2, "ex") == 0){
        return 2;
    } else {
        return 3;
    }
}

void fifo_send(int fd, int op, int pid, int indx){
    if(op == 1){
        char tmp[32];
        sprintf(tmp, "%d-%d,", indx, pid);
        write(fd, tmp, strlen(tmp) * sizeof(char));
    } else if(op == 2){
        write(fd, "0-ex,", sizeof("0-ex,"));
    }
    
}

int get_fifo_index_set_shr_mem(int *shm, int shmc){
    int indx = shm[0];
    shm[0] += 1;
    return indx;
}

void register_shr_mem(int *shm, int shmc, int indx, int pid, int ptts){
    shm[1+2*indx]=pid;
    shm[1+2*indx+1]=ptts;
}

int is_all_cooled_down(int *shm, int shmc){
    int res = 1;
    for(int i = 2; i < shmc; i+=2){
        if(shm[i] != 0){
            res = 0;
            break;
        }
    }
    return res;
}

int get_potato(int *shm, int shmc, int pid){
    for(int i = 1; i < shmc; i+=2){
        if(shm[i] == pid){
            return shm[i+1];
        }
    }
    return -1;
}

void dec_potato(int *shm, int shmc, int pid){
    for(int i = 1; i < shmc; i+=2){
        if(shm[i] == pid){
            shm[i+1] -= 1;
            break;
        }
    }
}

int all_processes_initalized(int *shm, int shmc, int fifo_pathsc){
    return shm[0] >= fifo_pathsc;
}

int get_rand(int u_bound){
    return rand() % u_bound;
}

int main(int argc, char **argv){
    srand(time(NULL));

    int has_porato_or_not;
    char shared_memory_name[128];
    char fifo_addresses_file_path[256];
    char semaphore_name[128];

    int fifo_pathsc;
    char **fifo_paths;

    read_parameters(argc, argv, &has_porato_or_not, shared_memory_name, fifo_addresses_file_path, semaphore_name);

    read_fifo_paths(&fifo_pathsc, &fifo_paths, fifo_addresses_file_path);

    int shmc;
    int *shm;

    int smd = shm_open(shared_memory_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(smd == -1){
        fprintf(stderr, "Error: Failed to open shared memory.\nProgram will be terminated.\n");
        exit(0);
    }
    shmc = 1 + 2 * fifo_pathsc;
    ftruncate(smd, shmc * sizeof(int));
    shm = (int *) mmap(NULL, shmc * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, smd, 0);
    if(shm == MAP_FAILED){
        fprintf(stderr, "Error: Failed to map shared memory.\nProgram will be terminated.\n");
        exit(0);
    }

    sem_t *sp = sem_open(semaphore_name, O_CREAT, S_IRUSR | S_IWUSR , 1);
    if(sp == SEM_FAILED){
        fprintf(stderr, "Error: Semaphore can not open semaphore.\nProgram will be terminated.\n");
        exit(0);
    }

    int str_fifo_remotesc;
    char **str_fifo_remotes;
    char *str_fifo_local;

    if(sem_wait(sp) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nProgram will be terminated.\n");
        exit(0);
    }
    //CHECK RUNNED PROGRAM COUNT ISNT GREATER THAN FIFOS FILE LINES
    int index = get_fifo_index_set_shr_mem(shm, shmc);

    //CHECK RUNNED PROGRAM COUNT ISNT GREATER THAN FIFOS FILE LINES
    init_fifo_conns(index, fifo_pathsc, fifo_paths, &str_fifo_remotesc, &str_fifo_remotes, &str_fifo_local);

    //CHECK RUNNED PROGRAM COUNT ISNT GREATER THAN FIFOS FILE LINES
    register_shr_mem(shm, shmc, index, getpid(), has_porato_or_not);

    int fifo_remotesc = str_fifo_remotesc;
    int fifo_remotes[fifo_remotesc];
    int fifo_local;

    if(sem_post(sp) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nProgram will be terminated.\n");
        exit(0);
    }

    connect_fifos(index, fifo_remotesc, fifo_remotes, &fifo_local, str_fifo_remotesc, str_fifo_remotes, str_fifo_local);

    if(get_potato(shm, shmc, getpid()) > 0){
        int idx = get_rand(fifo_remotesc);
        printf("pid = %d sending potato number %d to %s. This is switch number %d.\n", getpid(), getpid(), str_fifo_remotes[idx], get_potato(shm, shmc, getpid()));
        fifo_send(fifo_remotes[idx], 1, getpid(), index);
    }

    int rec_potato;
    int rec_index;
    int ex = 0;

    while(ex == 0){
        switch(fifo_wait(fifo_local, &rec_potato, &rec_index)){
            case 1:
                if(sem_wait(sp) == -1){
                    fprintf(stderr, "Error: Semaphore exception.\nProgram will be terminated.\n");
                    exit(0);
                }
                printf("pid = %d receiving potato number %d from %s\n", getpid(), rec_potato, fifo_paths[rec_index]);
                dec_potato(shm, shmc, rec_potato);
                if(get_potato(shm, shmc, rec_potato) > 0){
                    int idx = get_rand(fifo_remotesc);
                    printf("pid = %d sending potato number %d to %s. This is switch number %d.\n", getpid(), rec_potato, str_fifo_remotes[idx], get_potato(shm, shmc, rec_potato));
                    fifo_send(fifo_remotes[idx], 1, rec_potato, index);
                } else {
                    printf("pid = %d potato number %d has cooled down.\n", getpid(), rec_potato);
                    if(is_all_cooled_down(shm, shmc)){
                        for(int i = 0; i < fifo_remotesc; i++){
                            fifo_send(fifo_remotes[i], 2, 0, 0);
                        }
                        ex = 1;
                    }
                }
                if(sem_post(sp) == -1){
                    fprintf(stderr, "Error: Semaphore exception.\nProgram will be terminated.\n");
                    exit(0);
                }
                break;
            case 2:
                ex = 1;
                break;
        }
    }
    
    disconnect_fifos(index, fifo_remotesc, fifo_remotes, &fifo_local);

    if(sem_close(sp) == -1) fprintf(stderr, "Warning: Semaphore couldn't be closed.\n");
    if(shm_unlink(shared_memory_name));
    if(munmap(shm, shmc * sizeof(int))) fprintf(stderr, "Warning: Couldn't unmap the shared memory.\n");
    if(close(smd) == -1) fprintf(stderr, "Warning: Shared memory couldn't be closed.\n");

    free_fifo_conns(str_fifo_remotesc, str_fifo_remotes, str_fifo_local);
    free_fifo_paths(fifo_pathsc, fifo_paths);
    return 0;
}