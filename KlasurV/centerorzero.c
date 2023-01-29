/*
Compile: make center_or_zero
Run: ./center_or_zero
make center_or_zero && ./center_or_zero
*/

#include "base.h"

// A list node.
typedef struct IntList IntList;
struct IntList
{
    int value;
    IntList *next;
};

// Prepend value to the front of the given list.
IntList *prepend(int value, IntList *next)
{
    IntList *node = xcalloc(1, sizeof(IntList));
    node->value = value;
    node->next = next;
    return node;
}

int listLenght(IntList *list){
    int count = 0;
    while(list != NULL){
        count++;
        list = list->next;
    }
    return count;
}

// Purpose statement.
int center_or_zero(IntList *list)
{
    // todo: implement
    int listcount = listLenght(list);
    if(listcount == 1 )return list->value;
    if(listcount % 2 == 1){
        listcount = (listcount - 1) / 2 ;
        for(int i = 0; i < listcount; i++){
            list = list->next;
        }
        return list->value;
    }
    return 0;
}

void test(void)
{
    test_equal_i(center_or_zero(NULL), 0);
    test_equal_i(center_or_zero(prepend(-10, NULL)), -10);

    test_equal_i(center_or_zero(prepend(1, prepend(10, NULL))), 0);

    test_equal_i(center_or_zero(prepend(2, prepend(1, prepend(-2, NULL)))), 1);
    test_equal_i(center_or_zero(prepend(2, prepend(-1, prepend(2, NULL)))), -1);

    test_equal_i(center_or_zero(prepend(1, prepend(-1, prepend(9, prepend(-2, prepend(2, NULL)))))), 9);
    test_equal_i(center_or_zero(prepend(1, prepend(2, prepend(-3, prepend(-4, NULL))))), 0);
}

int main(void)
{
    test();
    return 0;
}