#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "queue.h"

#define PATH_LEN 128

struct Student {
    char name[128];
    int q;
    int s;
    int c;
    int solved;
    int money;
    int busy;
};

struct st_thread_args {
    sem_t *sem;
    int *exit_code;
    int s;
    int *busy;
};

struct h_thread_args {
    sem_t *sem;
    int *exit_code;
    char *filepath;
    struct Queue *queue;
    int *filled;
};

void init_student(struct Student *student){
    memset(student->name, '\0', 128);
    student->q = 0;
    student->s = 0;
    student->c = 0;
    student->solved = 0;
    student->money = 0;
    student->busy = 0;
}

int is_unsigned_int(char *str){
    if(str == NULL) return 0;
    for(int i = 0; i < strlen(str); i++){
        if(!isdigit(str[i]) && !(i == strlen(str)-1 && str[i] == '\n')) return 0;
    }
    return 1;
}

void read_params(char *homework_filepath, char *students_filepath, int *budget, int argc, char *args[]){
    if(argc == 4){
        strcpy(homework_filepath, args[1]);
        strcpy(students_filepath, args[2]);
        for(int i = 0; i < strlen(args[3]); i++){
            if(!isdigit(args[3][i]) && (i != 0 || args[3][i] != '-')){
                fprintf(stderr, "Error: Budget should be an integer value.\n");
                exit(EXIT_FAILURE);
            }
        }
        *budget = atoi(args[3]);
        if(*budget <= 0){
            fprintf(stderr, "Error: Budget should be greater than 0.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Error: Program must receive exactly 3 parameters for homeworks file path, students file path and budget respectively.\n");
        exit(EXIT_FAILURE);
    }
}

int read_students_count(char *filepath){
    FILE *fp;
    if((fp = fopen(filepath, "r")) == NULL){
        fprintf(stderr, "Error: File opening failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char str[128];
    while(fgets(str, 128, fp) != NULL) count++;
    
    if(fclose(fp) != 0){
        fprintf(stderr, "Error: File closing failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return count;
}

void read_students(char *filepath, struct Student *students, int studentsc){
    FILE *fp;
    if((fp = fopen(filepath, "r")) == NULL){
        fprintf(stderr, "Error: File opening failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char str[128];
    char *token;
    for(int i = 0; i < studentsc && fgets(str, 128, fp) != NULL; i++){
        strcpy(students[i].name, strtok(str, " "));

        token = strtok(NULL, " ");
        if(!is_unsigned_int(token)){
            fprintf(stderr, "Error: The value for Q on line %d in the file %s must be a positive number.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }
        students[i].q = atoi(token);
        if(students[i].q > 5){
            fprintf(stderr, "Error: The value for Q on line %d in the file %s must be less than or equal to 5.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
        if(!is_unsigned_int(token)){
            fprintf(stderr, "Error: The value for S on line %d in the file %s must be a positive number.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }
        students[i].s = atoi(token);
        if(students[i].s > 5){
            fprintf(stderr, "Error: The value for S on line %d in the file %s must be less than or equal to 5.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
        if(!is_unsigned_int(token)){
            fprintf(stderr, "Error: The value for C on line %d in the file %s must be a positive number.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }
        students[i].c = atoi(token);
        if(students[i].c > 1000 || students[i].c < 100){
            fprintf(stderr, "Error: The value for S on line %d in the file %s must be between 100 and 1000.\nProgram will be terminated.\n", i + 1, filepath);
            exit(EXIT_FAILURE);
        }

        while(strtok(NULL, " ") != NULL);
    }

    if(fclose(fp) != 0){
        fprintf(stderr, "Error: File closing failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

int find_student(int budget, char c, int studentsc, struct Student *students){
    int result = -1;
    for(int i = 0; i < studentsc; i++){
        if(students[i].busy == 0 && budget >= students[i].c){
            if(c == 'q' || c == 'Q') {
                if((i != -1 || students[i].q > students[result].q)) result = i;
            } else if(c == 's' || c == 'S') {
                if((i != -1 || students[i].s > students[result].s)) result = i;
            } else if(c == 'c' || c == 'C') {
                if((i != -1 || students[i].c < students[result].c)) result = i;
            } else {
                break;
            }
        }
    }
    return result;
}

int has_budget(int budget, int studentsc, struct Student *students){
    for(int i = 0; i < studentsc; i++){
        if(students[i].c <= budget) return 1;
    }
    return 0;
}

void *h_thread(void *tmp_args){
    struct h_thread_args *args = tmp_args;

    FILE *fp;
    if((fp = fopen(args->filepath, "r")) == NULL){
        fprintf(stderr, "Error: File opening failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        *(args->exit_code) = 1;
        return NULL;
    }

    char c;
    while((c = fgetc(fp)) != EOF){
        if(c == 'q' || c == 's' || c == 'c' || c == 'Q' || c == 'S' || c == 'C'){
            sem_wait(args->sem);
            if(*(args->exit_code) == 1){
                sem_post(args->sem);
                break;
            } else {
                enqueue(args->queue, c);
                sem_post(args->sem);
            }
        } else if(c != '\n' && c != '\0') {
            fprintf(stderr, "Warning: Character %c inside file %s is not a valid character.\nIt will be ignored.\n", c, args->filepath);
        }
    }
    
    if(fclose(fp) != 0){
        fprintf(stderr, "Error: File closing failure.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
        *(args->exit_code) = 1;
        return NULL;
    }

    *(args->filled) = 1;
}

void *st_thread(void *tmp_args){
    struct st_thread_args args = *((struct st_thread_args *) tmp_args);

    while(1){
        sem_wait(args.sem);
        if(*(args.exit_code) == 1){
            break;
        } else {
            sleep(6 - args.s);
            *(args.busy) = 0;
        }
    }
}

void main_thread(int *exit_code, int *budget, int *queue_filled, struct Queue *queue, int studentsc, struct Student *students, sem_t *h_sem, sem_t *students_sem){
    while(!(*queue_filled == 1 && is_empty(queue)) && has_budget(*budget, studentsc, students)){
        sem_wait(h_sem);
        if(*exit_code == 1){
            sem_post(h_sem);
            break;
        } else {
            char hw = dequeue(queue);
            int idx;
            while((idx = find_student(*budget, hw, studentsc, students)) == -1);
            if(idx != -1){
                students[idx].busy = 1;
                sem_post(&(students_sem[idx]));
                *budget -= students[idx].c;
                students[idx].solved += 1;
                students[idx].money += students[idx].c;

                printf("%s is solving homework %c for %d, H has %dTl left.\n", students[idx].name, hw, students[idx].c, *budget);
            }
            sem_post(h_sem);
        }
    }

    if(*queue_filled == 1 && is_empty(queue)) printf("No more homeworks left or coming in, closing.\n");
    else if(!has_budget(*budget, studentsc, students))printf("Money is over, closing.\n");
}

int main(int argc, char *args[]){
    char homework_filepath[PATH_LEN];
    char students_filepath[PATH_LEN];
    int budget;

    memset(homework_filepath, '\0', PATH_LEN);
    memset(students_filepath, '\0', PATH_LEN);
    budget = 0;

    read_params(homework_filepath, students_filepath, &budget, argc, args);
    struct Queue queue;
    init_queue(&queue);
    
    int studentsc = read_students_count(students_filepath);
    struct Student students[studentsc];
    for(int i = 0; i < studentsc; i++)init_student(&(students[i]));
    read_students(students_filepath, students, studentsc);

    printf("%-16s %6s %6s %6s\n", "NAME", "Q", "S", "C");
    for(int i = 0; i < studentsc; i++){
        printf("%-16s %6d %6d %6d\n", students[i].name, students[i].q, students[i].s, students[i].c);
    }

    sem_t h_sem;
    sem_t students_sem[studentsc];

    pthread_t h_t;
    pthread_t students_t[studentsc];

    sem_init(&h_sem, 0, 1);
    for(int i = 0; i < studentsc; i++) sem_init(&(students_sem[i]), 0, 1);

    int queue_filled = 0;
    int exit_code = 0;

    struct h_thread_args args_h;
    
    args_h.filepath = homework_filepath;
    args_h.filled = &queue_filled;
    args_h.queue = &queue;
    args_h.sem = &h_sem;
    args_h.exit_code = &exit_code;

    pthread_create(&h_t, NULL, h_thread, &args_h);

    struct st_thread_args args_st[studentsc];
    for(int i = 0; i < studentsc; i++){
        args_st[i].exit_code = &exit_code;
        args_st[i].s = students[i].s;
        args_st[i].sem = &(students_sem[i]);
        args_st[i].busy = &(students[i].busy);

        pthread_create(&(students_t[i]), NULL, st_thread, &(args_st[i]));
    }

    main_thread(&exit_code, &budget, &queue_filled, &queue, studentsc, students, &h_sem, students_sem);

    exit_code = 1;

    for(int i = 0; i < studentsc; i++){
        if(sem_post(&(students_sem[i])) == -1){
            fprintf(stderr, "Error: Semaphore exception.\nReason: %s\nProgram will be terminated.\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    pthread_join(h_t, NULL);
    for(int i = 0; i < studentsc; i++) {
        pthread_join(students_t[i], NULL);
    }
    
    printf("Homeworks solved and money made by the students:\n");
    for(int i = 0; i < studentsc; i++){
        printf("%-16s %6d %6d\n", students[i].name, students[i].solved, students[i].money);
    }

    sem_destroy(&h_sem);
    for(int i = 0; i < studentsc; i++) sem_destroy(&(students_sem[i]));
}
