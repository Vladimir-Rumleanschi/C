/*
make row_sum && ./row_sum
*/

#include "base.h"

// <purpose statement>
int *row_sum(int *a, int rows, int cols)
{
    // implement
    int outputcount = 0;
    int* output = xmalloc(rows * sizeof(int));
    for(int i = 0; i < rows * cols; i++){
        output[outputcount] = a[i];
        i++;
        for(int j  =  1; j < cols; j++){
            output[outputcount] *= a[i];
            if(!((i + 1 )% cols == 0))i++;
        }
        outputcount++;
    }
    return output;
}

void test(void)
{
    int a[3][3] = {
        {1, 2, 3},
        {-1, -2, -3},
        {3, 4, 5},
    };
    int *margin = row_sum((int *)a, 3, 3);
    int expected[] = {6, -6, 60};
    ia_test_equal(a_of_buffer(margin, 3, sizeof(int)),
                  a_of_buffer(expected, 3, sizeof(int)));
}

int main(void)
{
    test();
    return 0;
}