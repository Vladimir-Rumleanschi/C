#include "base.h"

typedef struct Stack{
    char paranthese;
    struct Stack* nextpar;
}Stack;


struct Stack* newstack(char par){
    struct Stack* stack = xcalloc(1, sizeof(struct Stack));
    stack->paranthese = par;
    stack->nextpar = NULL;
    return stack;
}

void stack_free(Stack *stack){
    Stack *next = stack;
    next = next->nextpar;
    free(stack);
}

Stack* stack_push(Stack *stack, char value){
  
    if (stack == NULL){
        stack = newstack(value);
    }else{
        Stack *temp = newstack(stack->paranthese);
        temp->nextpar = stack->nextpar;
        stack->nextpar = temp;
        stack->paranthese = value;
    }
    return stack;
}

Stack* stack_pop(Stack *stack)
{
    // todo
    if(stack == NULL)return stack;
    if (stack->nextpar != NULL){
        Stack* tempstack = stack->nextpar;
        free(stack);
        return tempstack;
    }else{
        stack_free(stack);
        stack = NULL;
    }
    return stack;
}

bool checkForClosedPar(char par){
    String closedpar = ")]}>";
    for(int i = 0; i < 4; i++){
        if(closedpar[i] == par)return true;
    }
    return false;
}

bool checkParPaars(char openpar,char closepar){
    if(closepar == ')' && openpar == '(')return true;
    if(closepar == ']' && openpar == '[')return true;
    if(closepar == '}' && openpar == '{')return true;
    if(closepar == '>' && openpar == '<')return true;
    return false;
}

void freeAllStack(Stack* stack){
    while(stack != NULL){
        Stack* tempstack = stack->nextpar;
        free(stack);
        stack = tempstack;
    }
}


bool verify_parentheses(String text) {
    // TODO

    String parantheses = "()[]{}<>";
    struct Stack* stack = NULL;
    for(int i = 0; i < strlen(text); i++){
        for(int j = 0; j < 8; j++ ){
            if(text[i] == parantheses[j]){
                if(checkForClosedPar(text[i])){
                    if(stack == NULL){
                        return false;
                    }else if (checkParPaars(stack->paranthese,text[i])){
                        stack = stack_pop(stack);
                    }else{
                        freeAllStack(stack);
                        return false;
                    } 
                }else{
                    stack = stack_push(stack,text[i]);
                }
            }
        }
    }
    if(stack != NULL){
        freeAllStack(stack);
        return false;
    }
    return true;
}

int main(void) {
    report_memory_leaks(true);

    test_equal_i(verify_parentheses(""), true);
    test_equal_i(verify_parentheses("Hello World"), true);
    test_equal_i(verify_parentheses("()"), true);
    test_equal_i(verify_parentheses("<{[()]}>"), true);
    test_equal_i(verify_parentheses("<{[)]}>"), false);
    test_equal_i(verify_parentheses("( Test ) "), true);
    test_equal_i(verify_parentheses("(1+2)*[2+3+(1 + 6/5)]"), true);
    test_equal_i(verify_parentheses("(an unmatched left parenthesis creates an unresolved tension that will stay with you all day"), false);
    test_equal_i(verify_parentheses("< [ > ]"), false);
    test_equal_i(verify_parentheses("<{[()]}"), false);
    test_equal_i(verify_parentheses("(<<({[({<{<({<([[[<[{(<{(<{{<[{<{{{<<{([<<<{{[{<<[[(([{[[[([(({()}))])]]]}]))]]>>}]}}>>>])}>>}}}>}]>}}>)}>)}]>]]])>})>}>})]})>>)"), true);

    return 0;
}
