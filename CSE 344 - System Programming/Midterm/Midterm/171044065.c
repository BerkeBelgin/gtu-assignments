#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <errno.h>

#define MAX_PATHNAME_SIZE 256
#define MAX_FIFONAME_SIZE 32
#define FILE_SHM_NAME "mdtrm_file_shm"
#define FILE_SEM_NAME "mdtrm_file_sem"
#define BUFFER_SHM_NAME "mdtrm_buffer_shm"
#define BUFFER_SEM_NAME "mdtrm_buffer_sem"
#define RECORDS_SHM_NAME "mdtrm_records_shm"
#define RECORDS_SEM_NAME "mdtrm_records_sem"

void err_exit(){
    if(kill(0, SIGKILL) == 0)
        while(wait(NULL) > 0);
    exit(EXIT_FAILURE);
    
}

void read_parameters(int argc, char **argv, int *nursesc, int *vaccinatorsc, int *citizensc, int *buffer_size, int *shots_per_citizenc, char *pathname){
    int n = -1;
    int v = -1;
    int c = -1;
    int b = -1;
    int t = -1;
    char i[MAX_PATHNAME_SIZE];
    memset(i, '\0', MAX_PATHNAME_SIZE);
    
    int opt;
    while((opt = getopt(argc, argv, ":n:v:c:b:t:i:")) != -1){
        switch(opt){
            case 'n':
                if(optarg != NULL && strlen(optarg) > 0){
                    n = atoi(optarg);
                }
                break;
            case 'v':
                if(optarg != NULL && strlen(optarg) > 0){
                    v = atoi(optarg);
                }
                break;
            case 'c':
                if(optarg != NULL && strlen(optarg) > 0){
                    c = atoi(optarg);
                }
                break;
            case 'b':
                if(optarg != NULL && strlen(optarg) > 0){
                    b = atoi(optarg);
                }
                break;
            case 't':
                if(optarg != NULL && strlen(optarg) > 0){
                    t = atoi(optarg);
                }
                break;
            case 'i':
                if(optarg != NULL && strlen(optarg) > 0){
                    strcpy(i, optarg);
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
    
    if(n < 2){
        fprintf(stderr, "Error: Command line argument -n must have a value greater than or equal to 2.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else if(v < 2){
        fprintf(stderr, "Error: Command line argument -v must have a value greater than or equal to 2.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else if(c < 3){
        fprintf(stderr, "Error: Command line argument -c must have a value greater than or equal to 3.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else if(t < 1){
        fprintf(stderr, "Error: Command line argument -t must must have a value greater than or equal to 1.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else if(b < t * c + 1){
        fprintf(stderr, "Error: Command line argument -b must have a value greater than or equal to t * c + 1.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else if(strlen(i) < 1){
        fprintf(stderr, "Error: Command line argument -i must be provided.\nProgram will be terminated.\n");
        exit(EXIT_FAILURE);
    } else {
        *nursesc = n;
        *vaccinatorsc = v;
        *citizensc = c;
        *buffer_size = b;
        *shots_per_citizenc = t;
        strcpy(pathname, i);
    }
}

int get_file_index(int *file_shm){
    return file_shm[0];
}

void increment_file_index(int *file_shm){
    file_shm[0] += 1;
}

int get_1_count(int buffer_shmc, char *buffer_shm){
    int res = 0;
    for(int i = 0; i < buffer_shmc; i++){
        if(buffer_shm[i] == '1') res++;
    }
    return res;
}

int get_2_count(int buffer_shmc, char *buffer_shm){
    int res = 0;
    for(int i = 0; i < buffer_shmc; i++){
        if(buffer_shm[i] == '2') res++;
    }
    return res;
}

int get_buff_index(int buffer_shmc, char *buffer_shm){
    for(int i = 0; i < buffer_shmc; i++){
        if(buffer_shm[i] == '0') return i;
    }
    return -1;
}

void add_buff(char c, int buffer_shmc, char *buffer_shm){
    for(int i = 0; i < buffer_shmc; i++){
        if(buffer_shm[i] == '0') {
            buffer_shm[i] = c;
            break;
        }
    }
}

int pop_buff(int buffer_shmc, char *buffer_shm){
    int idx1 = -1;
    int idx2 = -1;

    for(int i = 0; i < buffer_shmc; i++){
        if(idx1 == -1 && buffer_shm[i] == '1') idx1 = i;
        else if(idx2 == -1 && buffer_shm[i] == '2') idx2 = i;
    }

    if(idx1 != -1 && idx2 != -1){
        buffer_shm[idx1] = '0';
        buffer_shm[idx2] = '0';
        for(int i = 0, j = 0; i < buffer_shmc; i++){
            if(buffer_shm[j] == '0') {
                if(buffer_shm[i] != '0'){
                    buffer_shm[j] = buffer_shm[i];
                    buffer_shm[i] = '0';
                    j++;
                }
            } else {
                j++;
            }
        }
        return 0;
    }else return -1;
}

int get_next_pid_rec(int records_shm_y, int records_shm_x, int *records_shm){
    int idx = -1;
    int pid = -1;
    int shots = -1;
    for(int i = 0; i < records_shm_y; i++){
        if(idx == -1){
            idx = i*records_shm_x;
            pid = records_shm[i*records_shm_x];
            shots = records_shm[i*records_shm_x+1];
        } else if(shots > records_shm[i*records_shm_x+1]){
            idx = i*records_shm_x;
            pid = records_shm[i*records_shm_x];
            shots = records_shm[i*records_shm_x+1];
        } else if(pid > records_shm[i*records_shm_x]){
            idx = i*records_shm_x;
            pid = records_shm[i*records_shm_x];
            shots = records_shm[i*records_shm_x+1];
        }
    }

    records_shm[idx+1] += 1;

    return pid;
}

int remaining_citizens_rec(int records_shm_y, int records_shm_x, int *records_shm, int shots_per_citizenc){
    int res = 0;
    for(int i = 0; i < records_shm_y; i++){
        if(records_shm[i] < shots_per_citizenc) res++;
    }
    return res;
}

int all_vaccinated_rec(int records_shm_y, int records_shm_x, int *records_shm, int shots_per_citizenc){
    for(int i = 0; i < records_shm_y; i++){
        if(records_shm[i] < shots_per_citizenc) return 0;
    }
    return 1;
}

void read_file(char *filepath, int buffer_shmc, char *buffer_shm, sem_t *buffer_sem_p, int *file_shm, sem_t *file_sem_p){
    FILE *fp = fopen(filepath, "r");
    if(fp == NULL){
        fprintf(stderr, "Error: File couldn't be opened.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }

    char c;
    do {
        if(sem_wait(buffer_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            kill(getppid(), SIGUSR1);
        }
        int buff_idx = get_buff_index(buffer_shmc, buffer_shm);

        if(buff_idx != -1){
            if(sem_wait(file_sem_p) == -1){
                fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
                kill(getppid(), SIGUSR1);
            }
            int file_idx = get_file_index(file_shm);

            if(fseek(fp, file_idx, SEEK_SET) != 0){
                fprintf(stderr, "Error: File reading failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
                kill(getppid(), SIGUSR1);
            }
            c = fgetc(fp);
            if(c != EOF){
                add_buff(c, buffer_shmc, buffer_shm);
                increment_file_index(file_shm);
                printf("Nurse pid = %d has brought vaccine %c: the clinic has %d vaccine 1 and %d vaccine 2\n", getpid(), c, get_1_count(buffer_shmc, buffer_shm), get_2_count(buffer_shmc, buffer_shm));
            }

            if(sem_post(file_sem_p) == -1){
                fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
                kill(getppid(), SIGUSR1);
            }
        }
        if(sem_post(buffer_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            kill(getppid(), SIGUSR1);
        }
    } while (c != EOF);

    if(fclose(fp) != 0){
        fprintf(stderr, "Error: File couldn't be closed.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }
}

void connect_local_fifo(int pid, int *local_fifo_fd){
    char fifo_name[MAX_FIFONAME_SIZE];
    sprintf(fifo_name, "fifo_%d", pid);
    *local_fifo_fd = open(fifo_name, O_RDONLY);
}

void connect_remote_fifos(int pidc, int *pids, int *remote_fifo_fds){
    char fifo_name[MAX_FIFONAME_SIZE];
    for(int i = 0, j = 0; i < pidc; i++){
        sprintf(fifo_name, "fifo_%d", pids[i]);
        remote_fifo_fds[i] = open(fifo_name, O_WRONLY);
    }
}

void disconnect_local_fifo(int local_fifo_fd){
    close(local_fifo_fd);
}

void disconnect_remote_fifos(int remote_fifo_fdsc, int *remote_fifo_fds){
    for(int i = 0, j = 0; i < remote_fifo_fdsc; i++){
        close(remote_fifo_fds[i]);
    }
}

int fifo_wait(int fd){
    char tmp[32];
    memset(tmp, '\0', 32);
    char c;
    while(read(fd, &c, 1) > 0){
        if(c == ' ') break;
        strncat(tmp, &c, 1);
    }
    return atoi(tmp);
}

void fifo_send(int fd, int pid){
    char tmp[32];
    sprintf(tmp, "%d ", pid);
    write(fd, tmp, strlen(tmp) * sizeof(char));
}

void p_nurse(char *filepath, int buffer_shmc, char *buffer_shm, sem_t *buffer_sem_p, int *file_shm, sem_t *file_sem_p){
    read_file(filepath, buffer_shmc, buffer_shm, buffer_sem_p, file_shm, file_sem_p);
    printf("Nurse pid = %d has carried all vaccines to the buffer. It is terminating\n", getpid());
}

void p_vaccinator(int buffer_shmc, char *buffer_shm, sem_t *buffer_sem_p, int records_shm_y, int records_shm_x, int records_shmc, int *records_shm, sem_t *records_sem_p, int shots_per_citizenc){
    int local_fifo_fd;
    int remote_fifo_fdsc = records_shm_y;
    int remote_fifo_fds[remote_fifo_fdsc];

    if(sem_wait(records_sem_p) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }
    if(sem_post(records_sem_p) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }

    connect_local_fifo(getpid(), &local_fifo_fd);

    int pidc = remote_fifo_fdsc;
    int pids[pidc];
    for(int i = 0; i < pidc; i++)pids[i] = records_shm[i * records_shm_x];

    connect_remote_fifos(pidc, pids, remote_fifo_fds);
    
    int vac_count = 0;
    int ex = 0;
    int fd;
    do {
        if(sem_wait(buffer_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            kill(getppid(), SIGUSR1);
        }

        int pop_vac = pop_buff(buffer_shmc, buffer_shm);
        
        if(sem_post(buffer_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            kill(getppid(), SIGUSR1);
        }

        if(pop_vac != -1){
            if(sem_wait(records_sem_p) == -1){
                fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
                kill(getppid(), SIGUSR1);
            }

            int pid = get_next_pid_rec(records_shm_y, records_shm_x, records_shm);
            vac_count += 2;

            if(sem_post(records_sem_p) == -1){
                fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
                kill(getppid(), SIGUSR1);
            }

            fd = 0;
            for(int i = 0; i < pidc; i++){
                if(pids[i] == pid){
                    fd = remote_fifo_fds[i];
                    break;
                }
            }

            printf("Vaccinator pid = %d is inviting citizen pid = %d to the clinic.\n", getpid(), pid);
            fifo_send(fd, getpid());
            fifo_wait(local_fifo_fd);

        } else if(all_vaccinated_rec(records_shm_y, records_shm_x, records_shm, shots_per_citizenc) == 1) {
            printf("Vaccinator pid = %d has vaccinated %d doses. All citizens have been vaccinated. It is terminating\n", getpid(), vac_count);
            ex = 1;
        }
    } while(ex == 0);

    disconnect_remote_fifos(remote_fifo_fdsc, remote_fifo_fds);
    disconnect_local_fifo(local_fifo_fd);
}

void p_citizen(int vaccinatorsc, int vaccinator_pids[vaccinatorsc], int shots_per_citizenc, int buffer_shmc, char *buffer_shm, int records_shm_y, int records_shm_x, int *records_shm, sem_t *records_sem_p){
    int local_fifo_fd;
    int remote_fifo_fdsc = vaccinatorsc;
    int remote_fifo_fds[remote_fifo_fdsc];

    if(sem_wait(records_sem_p) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }
    if(sem_post(records_sem_p) == -1){
        fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        kill(getppid(), SIGUSR1);
    }

    connect_remote_fifos(vaccinatorsc, vaccinator_pids, remote_fifo_fds);
    connect_local_fifo(getpid(), &local_fifo_fd);

    int pid;
    int fd;
    int i = 0;
    char *th;
    while(i < shots_per_citizenc){
        pid = fifo_wait(local_fifo_fd);

        if(i == 0)th = "st\0";
        else if(i == 1)th = "nd\0";
        else if(i == 2)th = "rd\0";
        else th = "th\0";

        printf("Citizen pid = %d is vaccinated for the %d%s time. The clinic has %d vaccine 1 and %d vaccine 2\n", getpid(), i+1, th, get_1_count(buffer_shmc, buffer_shm), get_2_count(buffer_shmc, buffer_shm));
        
        fd = 0;
        for(int j = 0; j < vaccinatorsc; j++){
            if(vaccinator_pids[j] == pid){
                fd = remote_fifo_fds[j];
                break;
            }
        }

        if(fd != 0){
            fifo_send(fd, getpid());
            i++;
        }
    }
    printf("Citizen pid = %d is leaving. Remaining citizens to vaccinate %d\n", getpid(), remaining_citizens_rec(records_shm_y, records_shm_x, records_shm, shots_per_citizenc));
    disconnect_local_fifo(local_fifo_fd);
    disconnect_remote_fifos(remote_fifo_fdsc, remote_fifo_fds);
}

void open_shm_sem(char *smh_name, char *sem_name, int *shm_fd, int shm_size, void **shm, sem_t **sem_p){
    *shm_fd = shm_open(smh_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(*shm_fd == -1){
        fprintf(stderr, "Error: Failed to open shared memory.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    ftruncate(*shm_fd, shm_size);
    *shm = (int *) mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, *shm_fd, 0);
    if(*shm == MAP_FAILED){
        fprintf(stderr, "Error: Failed to map shared memory.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    *sem_p = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR , 1);
    if(*sem_p == SEM_FAILED){
        fprintf(stderr, "Error: Failed to open semaphore.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void close_shm_sem(char *smh_name, int shm_fd, int shm_size, void *shm, sem_t *sem_p){
    if(sem_close(sem_p) == -1) 
        fprintf(stderr, "Warning: Semaphore couldn't be closed.\nReason: %s\n", strerror(errno));
    if(shm_unlink(smh_name));
    if(munmap(shm, shm_size))
        fprintf(stderr, "Warning: Couldn't unmap the shared memory.\nReason: %s\n", strerror(errno));
    if(close(shm_fd) == -1)
        fprintf(stderr, "Warning: Shared memory couldn't be closed.\nReason: %s\n", strerror(errno));
}

void init_signal_handler(){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);

    struct sigaction sa;
    sa.sa_handler = &err_exit;
    sa.sa_flags = 0;
    sa.sa_mask = sigset;
    sigaction(SIGUSR1, &sa, NULL);
}

int main(int argc, char *argv[]){
    int nursesc;
    int vaccinatorsc;
    int citizensc;
    int buffer_size;
    int shots_per_citizenc;
    char pathname[MAX_PATHNAME_SIZE];

    read_parameters(argc, argv, &nursesc, &vaccinatorsc, &citizensc, &buffer_size, &shots_per_citizenc, pathname);
    init_signal_handler();

    int file_shm_fd;
    int file_shmc = 1;
    void *file_shm_p;
    sem_t *file_sem_p;

    int buffer_shm_fd;
    int buffer_shmc = buffer_size;
    void *buffer_shm_p;
    sem_t *buffer_sem_p;

    int records_shm_fd;
    int records_shm_y = citizensc;
    int records_shm_x = 2;
    int records_shmc = records_shm_y * records_shm_x;
    void *records_shm_p;
    sem_t *records_sem_p;

    open_shm_sem(FILE_SHM_NAME, FILE_SEM_NAME, &file_shm_fd, file_shmc * sizeof(int), &file_shm_p, &file_sem_p);
    open_shm_sem(BUFFER_SHM_NAME, BUFFER_SEM_NAME, &buffer_shm_fd, buffer_shmc * sizeof(char), &buffer_shm_p, &buffer_sem_p);
    open_shm_sem(RECORDS_SHM_NAME, RECORDS_SEM_NAME, &records_shm_fd, records_shmc * sizeof(int), &records_shm_p, &records_sem_p);

    int *file_shm = (int *) file_shm_p;
    char *buffer_shm = (char *) buffer_shm_p;
    int *records_shm = (int *) records_shm_p;


    for(int i = 0; i < file_shmc; i++)
        file_shm[i] = 0;
    for(int i = 0; i < buffer_shmc; i++)
        buffer_shm[i] = '0';
    for(int i = 0; i < records_shmc; i++)
        records_shm[i] = 0;

    int nurse_pids[nursesc];
    int vaccinator_pids[vaccinatorsc];
    int citizen_pids[citizensc];

    printf("Welcome to the GTU 344 clinic. Number of citizens to vaccinate c = %d with t = %d doses.\n", citizensc, shots_per_citizenc);

    int pid = 1;
    int ptype = 0;
    for(int i = 0; pid > 0 && i < nursesc; i++){
        if((pid = fork()) > 0){
            nurse_pids[i] = pid;
        } else if(pid == 0){
            ptype = 1;
        } else {
            fprintf(stderr, "Error: An error occured while creating processes.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            err_exit();
        }
    }

    if(pid > 0) {
        if(sem_wait(records_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            err_exit();
        }
    }

    for(int i = 0; pid > 0 && i < vaccinatorsc; i++){
        if((pid = fork()) > 0){
            vaccinator_pids[i] = pid;

            char fifo_name[MAX_FIFONAME_SIZE];
            sprintf(fifo_name, "fifo_%d", pid);
            mkfifo(fifo_name, S_IRUSR | S_IWUSR);
        } else if(pid == 0){
            ptype = 2;
        } else {
            fprintf(stderr, "Error: An error occured while creating processes.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            err_exit();
        }
    }

    for(int i = 0; pid > 0 && i < citizensc; i++){
        if((pid = fork()) > 0){
            citizen_pids[i] = pid;
            records_shm[i*2] = pid;
            records_shm[i*2+1] = 0;

            char fifo_name[MAX_FIFONAME_SIZE];
            sprintf(fifo_name, "fifo_%d", pid);
            mkfifo(fifo_name, S_IRUSR | S_IWUSR);
        } else if(pid == 0){
            ptype = 3;
        } else {
            fprintf(stderr, "Error: An error occured while creating processes.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            err_exit();
        }
    }

    if(pid > 0) {
        if(sem_post(records_sem_p) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            err_exit();
        }
    }

    switch(ptype){
        case 1:
            p_nurse(pathname, buffer_shmc, buffer_shm, buffer_sem_p, file_shm, file_sem_p);
            break;
        case 2:
            p_vaccinator(buffer_shmc, buffer_shm, buffer_sem_p, records_shm_y, records_shm_x, records_shmc, records_shm, records_sem_p, shots_per_citizenc);
            break;
        case 3:
            p_citizen(vaccinatorsc, vaccinator_pids, shots_per_citizenc, buffer_shmc, buffer_shm, records_shm_y, records_shm_x, records_shm, records_sem_p);
            break;
        default:
            break;
    }

    close_shm_sem(FILE_SHM_NAME, file_shm_fd, file_shmc * sizeof(int), file_shm_p, file_sem_p);
    close_shm_sem(BUFFER_SHM_NAME, buffer_shm_fd, buffer_shmc * sizeof(char), buffer_shm_p, buffer_sem_p);
    close_shm_sem(RECORDS_SHM_NAME, records_shm_fd, records_shmc * sizeof(int), records_shm_p, records_sem_p);

    while(wait(NULL) > 0);
    if(pid > 0)printf("The clinic is now closed. Stay healthy.\n");
    return 0;
}