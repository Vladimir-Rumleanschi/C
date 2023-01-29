#include "base.h"

void matrix_max(int*a, int rows, int cols, int*mval, int*mrow, int*mcol) {
    
        
    int value = a[0];
    for(int i = 0; i < rows * cols - 1 ; i++){
            if (value < a[i]){
                value = a[i];
        }
    }
    *mval = value;
    int r = 0;
    int c = 0;
    for(int j = 0 ;  j < rows * cols - 1 ; j++){
        if (r == rows)r =  0;
        if (c == cols)c = 0;
            if (*mval == a[j]){
                *mrow = r;
                *mcol = c;
                break;
        }
        r++;
        c++;
    }
    printf("m : %d , r : %d , c : %d\n",*mval,*mrow,*mcol);
  
}

void test(void) {
    int m, r, c;
    int a[3][3] = {{ 1, -1, 3 },{ 2, -2, 5 },{ 3, -3, 4 },};
    matrix_max((int*)a, 3, 3, &m, &r, &c);
    // m: 5, r: 1, c: 2
    int b[2][3] = {{ 1, -1, 3 },{ 7, -2, 5 },};
    matrix_max((int*)b, 2, 3, &m, &r, &c);
    // m: 7, r: 1, c: 0
    int x[2][3] = {{ 1, -1, 3 },{ 7, -2, 7 },};
    matrix_max((int*)x, 2, 3, &m, &r, &c);
    // m: 7, r: 1, c: 0
    // oder
    // m: 7, r: 1, c: 2
}

int main(void) {
    test();
    return 0;
}



