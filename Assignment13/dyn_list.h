#ifndef __DYN_LIST_H__
#define __DYN_LIST_H__


#include "base.h"

typedef struct Node {
    void* value;
    struct Node* next;
} Node;

Node* new_node(void* value, Node* next);


#endif
