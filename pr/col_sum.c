/*
make col_sum && ./col_sum
*/

#include "base.h"

// <purpose statement> rechnet die Summe des cols
int* col_sum(int* a, int rows, int cols) {
    // implement
    int* result = xcalloc(cols,sizeof(int));
    for(int i = 0; i < cols; i++){
        int err = 0;
        for(int j = i; j < rows * cols  ; j = j + cols ){
            err = err + a[j];
        }
        result[i] = err;
    }
    return result;
}

void test(void) {
    int a[3][3] = {
        { 1, -1, 3 }, 
        { 2, -2, 4 }, 
        { 3, -3, 5 }, 
    };
    int* margin = col_sum((int*)a, 3, 3);
    int expected[] = { 6, -6, 12 };
    ia_test_equal(a_of_buffer(margin, 3, sizeof(int)), 
                  a_of_buffer(expected, 3, sizeof(int)));
}

int main(void) {
    test();
    return 0;
}