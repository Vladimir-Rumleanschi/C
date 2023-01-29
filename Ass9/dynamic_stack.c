#include "base.h"

typedef struct DynamicStack {
    // todo
    int nr;
    struct DynamicStack* nextNr;
} DynamicStack;

DynamicStack * stack_new() {
    
    DynamicStack* stack = xcalloc(1,sizeof(DynamicStack));
    stack->nr = 0;
    stack->nextNr = NULL; 
    return stack;
}


void print_list(DynamicStack* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%d", list->nr);
        for (DynamicStack* n = list->nextNr; n != NULL; n = n->nextNr) {
            printf(", %d", n->nr);
        }
        printf("]");
    }
}

void stack_free(DynamicStack * stack) {
    // todo
    if(stack == NULL){
        return;
    }else{
        while(stack){
        DynamicStack* tempStack = stack->nextNr;
        free(stack);
        stack = tempStack;
    }
    }
}

void stack_push(DynamicStack * stack, int value) {
    // todo
    if(stack == NULL){
       
        stack = stack_new();
        stack->nr = value;
        print_list(stack);
    }else{
        DynamicStack* newStack = stack_new();
        newStack->nr = value;
        newStack->nextNr = stack;
        stack = newStack;
        print_list(stack);
    }


}

int stack_pop(DynamicStack * stack) {
    // todo
    return 0;
}

void test_stack_ops(DynamicStack * stack) {
    stack_push(stack, 42);
    stack_push(stack, 1);
    stack_push(stack, 13);
    test_equal_i(stack_pop(stack), 13);
    test_equal_i(stack_pop(stack), 1);
    stack_push(stack, 400);
    stack_push(stack, 500);
    stack_push(stack, 600);
    stack_push(stack, 700);
    test_equal_i(stack_pop(stack), 700);
    test_equal_i(stack_pop(stack), 600);
    test_equal_i(stack_pop(stack), 500);
    test_equal_i(stack_pop(stack), 400);
    test_equal_i(stack_pop(stack), 42);
    test_equal_i(stack_pop(stack), 0);
}

int main(void) {
    DynamicStack * stack = stack_new();
    test_stack_ops(stack);

    stack_free(stack);

    DynamicStack * stack2 = stack_new();
    stack_free(stack2);
}
