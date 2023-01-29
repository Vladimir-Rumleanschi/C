/*
Compile: make matrix
Run: ./matrix
make matrix && ./matrix
*/

#include "base.h" 

struct Matrix {
    int rows; // number of rows
    int cols; // number of columns
    double** data; // a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
};
typedef struct Matrix Matrix;

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix* new_matrix(int n_rows, int n_cols) {
    // todo: implement
    require("negative number", n_rows > 0 && n_cols > 0);
    double **new_matrix = xcalloc(n_rows,sizeof(double*));
    for (int ind = 0; ind < n_rows; ind++)
       {
        new_matrix[ind] = xcalloc( n_cols, sizeof(double));
    }
    Matrix* mat = xmalloc(sizeof(Matrix));
    mat->data = new_matrix;
    mat->rows = n_rows;
    mat->cols = n_cols;
    return mat;
}

/**
Creates a zero-initialized matrix of rows and columns matrix.
@param[in] data an array of doubles, ordered row-wise
@param[in] n_rows number of rows
@param[in] n_cols number of columns
@return a pointer to an array of n_rows pointers to rows; a row is an array of n_cols doubles 
*/
Matrix* copy_matrix(double* data, int n_rows, int n_cols) {
    // todo: implement
    require("negative number", n_rows > 0 && n_cols > 0);
    double **a = xmalloc(sizeof(double*) * n_rows);
    for (int b = 0; b < n_rows; b++) 
    {
        a[b] = xmalloc(sizeof(double) * n_cols);
    }
    int n_elements = 0;
    for (int i = 0; i < n_rows; i++) 
    {
        for (int j = 0; j < n_cols; j++) 
        {
            a[i][j] = data[n_elements];
            n_elements++;
        }
    }
    Matrix* mat = xmalloc(sizeof(Matrix));
    mat->data = a;
    mat->rows = n_rows;
    mat->cols = n_cols;
    return mat;
}

/**
Print a matrix.
@param[in] m the matrix to print
*/
void print_matrix(Matrix* m) {
    // todo: implement
    require("negative number", m->cols > 0 && m->rows > 0);
    for (int row = 0; row < m->rows; row++) 
    {
        for (int col = 0; col < m->cols; col++) 
        {
            printf("%.2f\t", m->data[row][col]);
        }
        printf("\n");
    }
}

/**
Transpose a matrix.
@param[in] a the first operand
@return a new matrix whose elements are transposed
*/
Matrix* transpose_matrix(/*in*/ Matrix* a) {
    // todo: implement
    require("negative number", a->cols > 0 && a->rows > 0);
    double **c = xmalloc(sizeof(double*) * a->cols);
    for (int i = 0; i < a->cols; i++)
     {
        c[i] = xmalloc(sizeof(double) * a->rows);
    }
    for (int row = 0; row < a->rows; row++) 
    {
        for (int col = 0; col < a->cols; col++) {
            c[col][row] = a->data[row][col]; 
        }
    } 
    Matrix* mat = xmalloc(sizeof(Matrix));
    mat->data = c;
    mat->rows = a->cols;
    mat->cols = a->rows;
    return mat;
    ensure("Die Funktion ist nict Null ", mat != NULL);
}

/**
Multiplies two matrices.
@param[in] a the first operand
@param[in] b the second operand
@return a new matrix that is the result of the multiplication of a * b
*/
Matrix* mul_matrices(/*in*/ Matrix* a, /*in*/ Matrix* b) {
    // todo: implement
    require("negative number", a->cols > 0 && a->rows > 0);
    require("Dimension", a->cols == b->rows);
    double **c = xmalloc(sizeof(double*) * a->rows);
    for (int i = 0; i < a->rows; i++) 
    {
        c[i] = xmalloc(sizeof(double) * b->cols);
    }
    for (int row = 0; row < a->rows; row++)
     {
        for (int col = 0; col < b->cols; col++) 
        {
            c[row][col] = 0;
            for (int k = 0; k < a->cols; k++)
             {
                c[row][col] += a->data[row][k] * b->data[k][col];
            }
        }
    } 
    Matrix* mat = xmalloc(sizeof(Matrix));
    mat->data = c;
    mat->rows = a->rows;
    mat->cols = b->cols;
    return mat;
    ensure("Die Funktion ist nict Null ", mat != NULL);
}
/**
Free a matrix.
@param[in] m the matrix to free
*/
void free_matrix(Matrix* m) {
    // todo: implement
    for (int row = 0; row < m->rows; row++)
{
        free(m->data[row]); 
    }
    free(m->data);
    free(m);
}

void matrix_test(void) {
    printf("Create empty matrix: \n");
    
    Matrix* m0 = new_matrix(7, 1);
    print_matrix(m0);
    
    printf("Copy matrix data from double[]\n");
    
    double a[] = { 
        1, 2, 3, 
        4, 5.123, 6, 
        7, 8, 9 };
    Matrix* m1 = copy_matrix(a, 3, 3);
    printf("m1:\n");
    print_matrix(m1);
    

    
    double a2[] = { 
        1, 2, 3, 3.5,
        4, 5, 6, 7};
    Matrix* m2 = copy_matrix(a2, 2, 4);
    printf("m2:\n");
    print_matrix(m2);
    
    
    
    printf("Transpose: m2\n");
    Matrix* m2t = transpose_matrix(m2);
    print_matrix(m2t);


    double a3[] = { 
        1, 2, 
        3, 4, 
        5, 6,
        7, 8};
    Matrix* m3 = copy_matrix(a3, 4, 2);
    printf("m3:\n");
    print_matrix(m3);

    printf("Multiplie m3 * m3t\n");
    Matrix* m3t = transpose_matrix(m3);
    printf("m3t:\n");
    print_matrix(m3t);
    
    Matrix* m4 = mul_matrices(m3, m3t);
    printf("m4:\n");
    print_matrix(m4);
    
    free_matrix(m0);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m2t);
    free_matrix(m3);
    free_matrix(m3t);
    free_matrix(m4);
    
}

int main(void) {
    report_memory_leaks(true);
    matrix_test();
    return 0;
}
