#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

#define MAX_QUEUE 100

struct _Queue{
    void *data[MAX_QUEUE];
    void** front;
    void** rear;
};

Queue *queue_new() {
    Queue *q = NULL;
    int i;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL) return NULL;
    for (i=0; i<MAX_QUEUE; i++)
        q->data[i] = NULL;
    
    q->front = &(q->data[0]);
    q->rear = &(q->data[0]);

    return q;
}

void queue_free(Queue *q) {
    free(q);
}

Bool queue_isEmpty(const Queue *q) {
    if (q == NULL) 
        return TRUE;
    
    if (q->front == q->rear) 
        return TRUE;
    
    return FALSE;
}

Status queue_push(Queue *q, const void *e) {
    if (q == NULL || e == NULL || _queue_isFull(q) == TRUE)
        return ERROR;
    
    *(q->rear) = e;

    q->rear = q->data + (q->rear + 1 - q->data) % MAX_QUEUE;

    return OK;
}

void *queue_pop(Queue *q) {
    void *e = NULL;
    if (q == NULL || queue_isEmpty(q) == TRUE) 
        return NULL;

    e = *(q->front);

    *(q->front) = NULL;

    q->front = q->data + (q->front + 1 - q->data) % MAX_QUEUE;

    return e;
}

void *queue_getFront(const Queue *q) {
    if (q == NULL || queue_isEmpty(q) == TRUE) 
        return NULL;
    
    return *(q->front);
}

void *queue_getBack(const Queue *q) {
    void **back = NULL;

    if (q == NULL || queue_isEmpty(q) == TRUE)
        return NULL;
    
    if (q->rear == q->data)
        back = q->data + MAX_QUEUE - 1;
    
    else
        back = q->rear - 1;

return *back;
}

size_t queue_size(const Queue *q){

    if(!q) return -1;
    if (queue_isEmpty(q)==TRUE) return 0;

    int i;
    size_t s=0;

    for (i=0;i<MAX_QUEUE;i++){
        if(q->data[i] != NULL)
            s++;
    }

    return s;
}