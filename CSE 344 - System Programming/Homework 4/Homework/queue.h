#include <stdio.h>
#include <stdlib.h>

struct Queue{
    struct Node *rear;
    struct Node *front;
};

struct Node{
    struct Node *prev;
    char data;
};

void init_queue(struct Queue *p_queue){
    p_queue->rear = NULL;
    p_queue->rear = NULL;
}

void enqueue(struct Queue *p_queue, char c){
    struct Node *node_p = (struct Node *) malloc(sizeof(struct Node));
    node_p->prev = NULL;
    node_p->data = c;

    struct Node *rear_p = p_queue->rear;
    if(p_queue->rear == NULL) p_queue->front = node_p;
    else p_queue->rear->prev = node_p;
    p_queue->rear = node_p;
}

int is_empty(struct Queue *p_queue){
    if(p_queue->rear == NULL)return 1;
    else return 0;
}

char dequeue(struct Queue *p_queue){
    if(p_queue->front == NULL){
        return '\0';
    } else {
        char data = p_queue->front->data;

        struct Node *node_p = p_queue->front;
        p_queue->front = p_queue->front->prev;
        if(p_queue->rear == node_p)p_queue->rear = NULL;
        free(node_p);

        return data;
    }
}
