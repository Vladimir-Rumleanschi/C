#ifndef __DYN_STACK_H__
#define __DYN_STACK_H__


#include "base.h"
#include "dyn_list.h"


typedef struct {
    Node* top;
} Stack;

Stack* new_stack(void) ;

void free_stack(Stack* s);

void push(Stack* s, void* x);

void* pop(Stack* s);

bool empty_stack(Stack* s);

#endif
