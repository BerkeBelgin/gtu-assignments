#include <stdio.h>
#include <stdlib.h>

typedef struct Queue{
    int size;
    struct Node *rear;
    struct Node *front;
} queue_t;

struct Node{
    struct Node *prev;
    int data;
};

void enqueue(struct Queue *p_queue, int n){
    struct Node *node_p = (struct Node *) malloc(sizeof(struct Node));
    node_p->prev = NULL;
    node_p->data = n;

    if(p_queue->rear == NULL) p_queue->front = node_p;
    else p_queue->rear->prev = node_p;
    p_queue->rear = node_p;

    p_queue->size += 1;
}

int dequeue(struct Queue *p_queue){
    if(p_queue->front == NULL){
        return 0;
    } else {
        int data = p_queue->front->data;

        struct Node *node_p = p_queue->front;
        p_queue->front = p_queue->front->prev;
        if(p_queue->rear == node_p)p_queue->rear = NULL;
        free(node_p);

        p_queue->size -= 1;

        return data;
    }
}

void init_queue(struct Queue *p_queue){
    p_queue->size = 0;
    p_queue->rear = NULL;
    p_queue->rear = NULL;
}

void clear_queue(struct Queue *p_queue){
    while(p_queue->size > 0) 
        dequeue(p_queue);
}

int q_size(struct Queue *p_queue){
    return p_queue->size;
}
