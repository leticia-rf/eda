#include <stdlib.h>
#include "queue.h"

void initialize(queue *q) {
    q->first = q->last = NULL;
}

void destroy(queue *q) {
    while(!empty(q))
        pop(q);
}

void* front(queue *q) {
    if(!empty(q))
        return q->first->data;
    return 0;
}

void push(queue *q, void* data) {
    qnode* new = (qnode*)malloc(sizeof(qnode)); 
    new->data = data;
    new->next = NULL;

    if (q->first == NULL) q->first = new; 
    else q->last->next = new;

    q->last = new;
}

void pop(queue *q) {
    if (!empty(q)) {
        qnode *n = q->first;
        q->first = n->next;
        if (q->first == NULL) q->last = NULL;
        free(n);
    }
}

int empty(queue *q) {
    return q->first == 0;
}