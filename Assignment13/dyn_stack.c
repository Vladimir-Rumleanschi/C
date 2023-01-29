#include "dyn_stack.h"


Stack* new_stack(void) {
    Stack* s = xcalloc(1, sizeof(Stack));
    s->top = NULL; // not necessary if using xcalloc
    return s;
}

void free_stack(Stack* s) {
    Node* next;
    for (Node* n = s->top; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(s);
}

bool empty_stack(Stack* s){
	return (s->top == NULL);
}

void push(Stack* s, void* x) {
    s->top = new_node(x, s->top);
}

void* pop(Stack* s) {
    if (s->top == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        Node* t = s->top;
        void* x = t->value;
        s->top = t->next;
        free(t);
        return x;
    }
}

