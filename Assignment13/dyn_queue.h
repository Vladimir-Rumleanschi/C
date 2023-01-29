#ifndef __DYN_QUEUE_H__
#define __DYN_QUEUE_H__


#include "base.h"
#include "dyn_list.h"


typedef struct {
    Node* head; // front of queue (first to be served)
    Node* tail; // back of queue (last to be served)
} Queue;

Queue* new_queue(void);

void free_queue(Queue* q);

void put_queue(Queue* q, void* x);

void* get_queue(Queue* q);

bool empty_queue(Queue* q);


#endif