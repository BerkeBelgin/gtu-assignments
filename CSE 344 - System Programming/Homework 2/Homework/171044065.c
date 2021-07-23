#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#define ROW_COUNT 8
#define COL_COUNT 8
#define COL_COUNT_R1 7
#define COL_COUNT_R2 7

struct pinfo{
    int idx;
    int pids[ROW_COUNT];
    int pidc;
};

int sigusr1 = 0;
int sigusr2 = 0;

int has_sigusr1(){
    return sigusr1 > 0;
}

void set_sigusr1(int sig){
    sigusr1++;
}

void reset_sigusr1(){
    sigusr1 = 0;
}

int has_sigusr2(){
    return sigusr2 > 0;
}

void set_sigusr2(int sig){
    sigusr2++;
}

void reset_sigusr2(){
    sigusr2 = 0;
}



void write_file(int fd, int n_line, float y){
    char str[2048];
    char str_appnd[256];
    FILE *fp = fdopen(fd, "r");
    fseek(fp, 0, SEEK_SET);
    for(int i = 0;fgets(str_appnd, 256, fp) != NULL;i++) {
        strcat(str, str_appnd);
        if(i == n_line){
            printf("HERE\n");
            char appnd[128];
            sprintf(appnd, ",%.1f\n", y);
            strcat(str_appnd, appnd);
        }
    }
    fp = fdopen(fd, "w");
    fputs(str, fp);
    return;
}

float calc_lagrange(float arr[], int n, int xi){
    float result = 0;
    for (int i=0; i<n; i+=2){
        float term = arr[i+1];
        for (int j=0;j<n;j+=2){
            if (j!=i) term = term*(xi - arr[j])/(float)(arr[i] - arr[j]);
        }
        result += term;
    }
    return result;
}

void read_coordinates(int fd, int n_line, float *coords, int ncoords){
    char line[256];
    FILE *fp = fdopen(fd, "r");
    fseek(fp, 0, SEEK_SET);
    for(int i = 0;fgets(line, 256, fp) != NULL;i++) {
        if(i == n_line){
            char *token = strtok(line, ",");
            for(int i = 0; i < ncoords && token != NULL; i++){
                token = strtok(NULL, ",");
                coords[i] = atof(token);
            }
            break;
        }
    }
    return;
}

void mother_proccess(struct pinfo info, sigset_t *sigset, int fd){
    while(!has_sigusr1())sigsuspend(sigset);
    reset_sigusr1();

    printf("RUN MAIN\n");
    //run

    for(int i = 0; i < info.pidc; i++){
        kill(info.pids[i], SIGUSR2);
    }

    while(!has_sigusr1())sigsuspend(sigset);
    reset_sigusr1();

    printf("RUN MAIN2\n");
    //run
}

void child_proccess(struct pinfo info, sigset_t *sigset, int fd){
    printf("RUN CHILD\n");
    //run
    int ncoords = COL_COUNT_R1*2;
    float coords[ncoords];
    for(int i = 0; i < ncoords; i++)coords[i]=0;

    if(info.idx == 0){
        while(!has_sigusr1())sigsuspend(sigset);
        reset_sigusr1();

        read_coordinates(fd, info.idx, coords, ncoords);
        for(int i = 0; i < ncoords; i++)printf("%.1f ", coords[i]);
        float res = calc_lagrange(coords, ncoords-2, coords[ncoords-2]);
        write_file(fd, info.idx, res);

        kill(getppid(), SIGUSR1);
    } else if(info.idx == ROW_COUNT - 1){
        read_coordinates(fd, info.idx, coords, ncoords);
        for(int i = 0; i < ncoords; i++)printf("%.1f ", coords[i]);
        float res = calc_lagrange(coords, ncoords-2, coords[ncoords-2]);
        write_file(fd, info.idx, res);

        kill(info.pids[info.idx - 1], SIGUSR1);
    } else {
        while(!has_sigusr1())sigsuspend(sigset);
        reset_sigusr1();

        read_coordinates(fd, info.idx, coords, ncoords);
        for(int i = 0; i < ncoords; i++)printf("%.1f ", coords[i]);
        float res = calc_lagrange(coords, ncoords-2, coords[ncoords-2]);
        write_file(fd, info.idx, res);

        kill(info.pids[info.idx - 1], SIGUSR1);
    }

    while(!has_sigusr2())sigsuspend(sigset);
    reset_sigusr2();

    printf("RUN CHILD2\n");
    //run

    if(info.idx == 0){
        while(!has_sigusr1())sigsuspend(sigset);
        reset_sigusr1();
        kill(getppid(), SIGUSR1);
    } else if(info.idx == ROW_COUNT - 1){
        kill(info.pids[info.idx - 1], SIGUSR1);
    } else {
        while(!has_sigusr1())sigsuspend(sigset);
        reset_sigusr1();
        kill(info.pids[info.idx - 1], SIGUSR1);
    }
}

void init_processes(struct pinfo *info){
    info->idx = -1;
    for(int i = 0; i < ROW_COUNT;i++) info->pids[i] = 0;
    info->pidc = 0;

    for(int i = 0; i < ROW_COUNT; i++){
        int pid = fork();
        if(pid == 0){;
            info->idx = i;
            return;
        } else if(pid < 0){// HERE WILL BE MODIFIED
            //info->pids[i] = pid;
            //info->pidc += 1;
            printf("DEAD BIRTH\n");
        } else{
            info->pids[i] = pid;
            info->pidc += 1;
        }
    }
    info->idx = ROW_COUNT;
    return;
}

int main(int argc, char **argv){
    sigset_t sigset;
    sigemptyset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);

    struct sigaction sa1;
    sa1.sa_handler = &set_sigusr1;
    sa1.sa_flags = 0;
    sa1.sa_mask = sigset;
    sigaction(SIGUSR1, &sa1, NULL);

    struct sigaction sa2;
    sa2.sa_handler = &set_sigusr2;
    sa2.sa_flags = 0;
    sa2.sa_mask = sigset;
    sigaction(SIGUSR2, &sa2, NULL);

    
    // sigdelset(&sigset, SIGCHLD);

    if(argc > 1){
        int fd = open(argv[1], O_RDWR);
        struct pinfo info;
        init_processes(&info);
        if(info.idx == ROW_COUNT)
            mother_proccess(info, &sigset, fd);
        else 
            child_proccess(info, &sigset, fd);
        close(fd);

        //check alive childs and terminate
        while(wait(NULL) != -1 || errno != ECHILD);
    } else {
        printf("File path as an argument needed.\n");
    }
    return 0;
}
