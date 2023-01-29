#include "base.h"

void mit(double* arr, int size){
double a = 0;
for(int i = 0; i < size; i++){
    a = a + arr[i];
}
a = a / size;
printf("%f",a);

}

void reverse(int* arr, int size){

for(int j = size - 1; j >= 0; j--){
    printf("%d \n",arr[j]);
}

}

void minmaxmed(int* arr, int size){
int temp = 0;
    for (int i = 0; i < size; i++) {     
        for (int j = i+1; j < size; j++) {     
           if(arr[i] > arr[j]) {    
               temp = arr[i];    
               arr[i] = arr[j];    
               arr[j] = temp;    
           }     
        }     
    }  
    for (int i = 0; i < size; i++) {     
        printf("%d ", arr[i]);    
    }    
    printf("\n");
    printf("min ist : %d \n", arr[0]);
    printf("max ist : %d \n", arr[size - 1]);
    if(size % 2 == 0){
        printf("median sind : %d und %d \n",arr[size / 2], arr[size / 2 + 1]);
    } else{
        int a = size / 2;
        printf("median ist : %d  \n",arr[a + 1]);
    }
}


double** matrix(int row, int call){
    double** matrix = xcalloc(row, sizeof(row));
    for(int i = 0; i < row ; i++){
        matrix[i] = xcalloc( call, sizeof(double));
    }
    return matrix;
}

bool compare(int** arr1 , int** arr2 ,int row1, int row2 , int coll1, int coll2){
    if (row1 == row2 && coll1 == coll2 ){
        for(int i = 0; i < row1 ; i++){
            for(int j  = 0; j < coll2; j++){
                if( arr1[i][j] != arr2[i][j])return false;
            }  
        }
    } else { 
        return false;
    }
    return true;
}

int** splita(int* sarr, int searr , int* indarr, int sind ){
    int** sparr = xcalloc(sind + 1,sizeof(int));
    for(int i = 0; i < sind ; i++){
        sparr[i] = xcalloc(1,sizeof(int));
    }
    sparr[sind] = xcalloc(searr - sind, sizeof(int));
    for(int b = 0; b < sind; b++){
        sparr[b][0] = sarr[indarr[b]];
    }
    int b = 0;
    for(int c = 0; c < searr; c++){
        bool pred = true;
        for (int i = 0; i < sind; i++){
            if (c == indarr[i]){
                pred = false;
                break;
            }
        }
        if(pred){
            sparr[sind][b] = sarr[c];
            b++;
        }   
    }
    return sparr;
}


int main(void){
    int ar[7] = {11 , 42, 15 ,22 , 10,52 , 3};
    int arr[4] = {0 , 3, 2, 4 };
    int** sarr = splita(ar,7,arr,4);

    for(int i = 0; i < 5; i++){
        printf("%d\n",sarr[i][0]);
        if(i == 3){
            printf("%d\n",sarr[4][1]);
            printf("%d\n",sarr[4][2]);
            printf("%d\n",sarr[4][3]);
        }
    }
    
    
    return 0;
}