/*
Compile: make dyn_queue
Run: ./dyn_queue
make dyn_queue && ./dyn_queue
*/

#include "dyn_queue.h"

Queue* new_queue(void) {
    Queue* q = xcalloc(1, sizeof(Queue));
    q->head = NULL; // not necessary if using xcalloc
    q->tail = NULL; // not necessary if using xcalloc
    return q;
}

void free_queue(Queue* q) {
    Node* next;
    for (Node* n = q->head; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(q);
}

void put_queue(Queue* q, void* x) {
    Node* t = new_node(x, NULL);
    if (q->tail != NULL) q->tail->next = t;
    q->tail = t;
    if (q->head == NULL) q->head = t;
}

void* get_queue(Queue* q) {
    Node* h = q->head;
    if (h == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        void* x = h->value;
        q->head = h->next;
        if (q->head == NULL) q->tail = NULL;
        free(h);
        return x;
    }
}

bool empty_queue(Queue* q) {
    return q->head == NULL;
}