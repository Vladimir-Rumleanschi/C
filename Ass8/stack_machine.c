#include "base.h"

#define STACK_SIZE  10

typedef enum {
    TAG_OPERATION,
    TAG_VALUE,
    TAG_EMPTY,
} Tag;

typedef struct {
    Tag tag;

    union {
        int value;
        char operation;
    };
} StackElement;

typedef struct {
    StackElement elements[STACK_SIZE];
    int stack_pointer;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c) {
    return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks if c is a digit
bool is_digit(char c){
    return c >= '0' && c <= '9';
}

StackElement make_StackElement(Tag tag) {
    return (StackElement) {
        .tag = tag,
        .value = 0,
    };
}

StackElement make_Value(int value) {
    StackElement e = make_StackElement(TAG_VALUE);
    e.value = value;
    return e;
}

StackElement make_Operation(char operation) {
    StackElement e = make_StackElement(TAG_OPERATION);
    e.operation = operation;
    return e;
}

bool is_empty(Stack* stack){
    return stack->stack_pointer < 0;
}


void print_stack_element(StackElement e) {
    // todo
}

void clear_stack(Stack* stack, int n) {
    // todo
}

void print_stack(Stack* stack, int n) {
    // todo
}

void push(StackElement element, Stack* stack, int n) {
    if(stack->stack_pointer < (n - 1)){
        stack->stack_pointer++;
        stack->elements[stack->stack_pointer] = element;
    }
}

StackElement pop(Stack* stack, int n) {
    StackElement e = stack->elements[stack->stack_pointer ];
    stack->elements[stack->stack_pointer] = make_StackElement(TAG_EMPTY);
    stack->stack_pointer--;
    return e;
}

void compute(Stack* stack, int n){
    // todo
}

int main(void) {
    Stack stack;
    clear_stack(&stack, STACK_SIZE);

    int input_size = 128;
    char input[input_size];

    for(int i = 0; i < input_size; i++){
        input[i] = '\0';
    }
    int input_index = 0;

    int c;
    while((c = getchar()) != 'q'){
        // todo
    }
    return 0;
}
