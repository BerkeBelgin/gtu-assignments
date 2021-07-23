#include <stdlib.h>
#include <string.h>

typedef struct llstrarr{
    unsigned int col_size;
    unsigned int row_size;
    struct Node *head;
    struct Node *tail;
} llstrarr_t;

struct Node{
    char **row;
    struct Node *next;
};

void init_llstrarr(struct llstrarr *llo, unsigned int col_size){
    llo->col_size = col_size;
    llo->row_size = 0;
    llo->head = NULL;
    llo->tail = NULL;
}

void destroy_llstrarr(struct llstrarr *llo){
    struct Node *node = llo->head;
    struct Node *next_node = node != NULL ? node->next : NULL;

    while(node != NULL){
        for(int i = 0; i < llo->col_size; i++){
            free(node->row[i]);
        }
        free(node->row);
        free(node);

        node = next_node;
        if(node != NULL)next_node = node->next;
    }

    llo->col_size = 0;
    llo->row_size = 0;
    llo->head = NULL;
    llo->tail = NULL;
}

void push_back_llstrarr(struct llstrarr *llo, char **strv){
    struct Node *node_p = (struct Node *) malloc(sizeof(struct Node));
    node_p->next = NULL;
    node_p->row = (char **) malloc(llo->col_size * sizeof(char *));
    for(int i = 0; i < llo->col_size; i++){
        node_p->row[i] = (char *) malloc((strlen(strv[i]) + 1) * sizeof(char));
        strcpy(node_p->row[i], strv[i]);
    }

    if(llo->tail == NULL) llo->head = node_p;
    else llo->tail->next = node_p;
    llo->tail = node_p;

    llo->row_size += 1;
}

int get_col_index_llstrarr(struct llstrarr *llo, char *col_name){
    if(col_name != NULL && llo->head != NULL){
        for(int i = 0; i < llo->col_size; i++){
            if(strcmp(llo->head->row[i], col_name) == 0)return i;
        }
    }
    return -1;
}

char *get_cols_llstrarr(struct llstrarr *llo, int colsc, int *cols, short distinct){
    struct Node *node = llo->head;

    unsigned int strc = 1;
    char *str = (char *) malloc(sizeof(char));
    str[0] = '\0';

    int distc = 0;
    while(node != NULL && distc < 2){
        for(int i = 0; i < colsc && i < llo->col_size; i++){
            if(cols[i] == 1){
                strc += (strlen(node->row[i]) + 1);
                str = realloc(str, strc);
                strcat(str, node->row[i]);
                strcat(str, ",");
            }
        }
        str[strlen(str)-1] = '\n';
        if(distinct)distc++;
        node = node->next;
    }
    return str;
}

char *update_cols_llstrarr(struct llstrarr *llo, int pairsc, int *cols, char **vals, int col, char *val){
    struct Node *node = llo->head;

    unsigned int strc = 1;
    char *str = (char *) malloc(sizeof(char));
    str[0] = '\0';

    if(node != NULL){
        node = node->next;
        while(node != NULL){
            if(strcmp(node->row[col], val) == 0){
                for(int i = 0; i < pairsc && i < llo->col_size; i++){
                    if(cols[i] == 1){
                        node->row[i] = (char *) realloc(node->row[i], sizeof(char) * (strlen(vals[i])+1));
                        strcpy(node->row[i], vals[i]);
                    }
                    strc += (strlen(node->row[i]) + 1);
                    str = realloc(str, strc);
                    strcat(str, node->row[i]);
                    strcat(str, ",");
                }
                str[strlen(str)-1] = '\n';
            }
            node = node->next;
        }
    }
    return str;
}

void free_get_llstrarr(char *str){
    free(str);
}

void print_table(struct llstrarr *llo){
    struct Node *node = llo->head;

    while(node != NULL){
        for(int i = 0; i < llo->col_size; i++){
            printf("%s ", node->row[i]);
        }
        printf("\n");
        node = node->next;
    }
}
