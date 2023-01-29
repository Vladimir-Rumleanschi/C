#include "base.h"

//Mat. Nr: 10037218 Vladimir Rumleanschi
//Mat. Nr: 10014985 Hoang Phuong Tran

typedef struct better_array_s {
    int length;
    int *array;
} BetterArray;

//todo: a)
bool compare(int *array_a, int length_a, int *array_b, int length_b) {
    if(length_a > length_b)return false;
    if(length_a < length_b)return false;
    if(length_a == length_b){

        if(length_a == 0)return true;//Wenn array_a Null ist, dann ist array_b auch Null.

        int i = 0; // index was durch den Array untersucht.

        while(length_b != i){
            if((array_a)[i] != (array_b)[i])return false; // wenn die Elmente nicht gleich sind dann geht es aus der Schleife raus und return false.
            //printf("%d == %d \n",(array_a)[i], (array_b[i]) );
            i++;
        }
        return true;
    }
    
    return false;
}

//todo: b)
int remove_negatives(int* array, int length) {

    for(int i = 0; i < length; i++){
        if ((array)[i] < 0){
            for(int j = i; j < length; j++){
                (array)[j] = (array)[j+1];
            }
            length--;//wenn ein Element < 0 ist, dann wird die Länge mit 1 gekürtzt
            i--;// wenn ein Element < 0 ist, dann müss die Schleife untersuchen ob der neuen 0. Element nicht < 0 ist 
        }
    }
    return length;
}

//todo: c)
BetterArray intersect(int *array_a, int length_a, int* array_b, int length_b) {
    BetterArray barr;
    if(compare((array_a), length_a,(array_b),length_b)){
        barr.length = length_a;
        barr.array = array_b;
        return barr;
    }
    else if ((length_a <= length_b) ) {

        int idx = 0;

        for(int i = 0; i < length_a; i++ ){
            for (int j = 0; j < length_b; j++){
                if ((array_a)[i] == (array_b)[j]){
                    (array_a)[idx] = (array_a)[i];
                    idx++;
                    }
                }
            }

        for (int i = 0; i < length_a; i++){
            if (i > idx - 1){
                for (int j = i; j < length_a; j++){
                    (array_a)[j] = (array_a)[j + 1];
                }
                length_a--; 
                i--;      
            }
        }

        //for(int i = 0; i < length_a; i++ ){
        //    printf("%d \n",(array_a)[i]);
        //    }
        barr.length =  idx;
        barr.array = array_a;
    }else{
        int idx = 0;

        for (int i = 0; i < length_b; i++){
            for (int j = 0; j < length_a; j++){
                if ((array_b)[i] == (array_a)[j]){
                    (array_b)[idx] = (array_a)[i];
                    idx++;
                }
            }
        }

        for (int i = 0; i < length_b; i++){
            if (i > idx - 1){
                for (int j = i; j < length_b; j++){
                    (array_b)[j] = (array_b)[j + 1];
                }
                length_b--;
                i--;
            }
        }

        //for (int i = 0; i < length_b; i++){
        //    printf("%d \n", (array_b)[i]);
        //}
        barr.length = idx;
        barr.array = array_b;
    }
    return barr;
}

//todo: d)
void merge_sorted_arrays(int *array_a, int length_a, int* array_b, int length_b, int* result, int length_result) {

    int idx_a = 0;
    int idx_b = 0;

    for(int i = 0; i < length_result; i++){

        if(length_a <= idx_a){
            (result)[i] = (array_b)[idx_b];
            idx_b++;
        }else if (length_b <= idx_b){
            (result)[i] = (array_b)[idx_b];
            idx_b++;
        }else{
            if ((array_a)[idx_a] == (array_b)[idx_b]){
                (result)[i] = (array_a)[idx_a];
                (result)[i + 1] = (array_b)[idx_b];
                i++;
                idx_a++;
                idx_b++;
            }
            else if ((array_a)[idx_a] < (array_b)[idx_b]){
                (result)[i] = (array_a)[idx_a];
                idx_a++;
            }else{
                (result)[i] = (array_b)[idx_b];
                idx_b++;
            }
        } 
    }
    //for (int i = 0; i < length_result; i++){
    //    printf("%d \n", (result)[i]);
    //}
}
// todo: e)
// Die Struktur BetterArray besagt die Länge des Array, also man müss nicht extra eine Schleife implementieren, was iterativ durch den Array die Elemente durchzählt.
// Strings sind in C als einen Char[] representiert.
// Man kann durch eine Schleife jedes Element des Strings durchzählen bis zum terminierten Byte ('\0')
// Nein weil die Char Elemente werden zu den Zahlen konvertiert
void test_compare(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    int a2[] = {1, 2, 3, -4, 8, 9};
    int length_a2 = 6;
    int a3[] = {1, -2, 3, 4, 8, 9};
    int length_a3 = 6;

    int a4[] = {1};
    int length_a4 = 1;

    int a5[] = {2};
    int length_a5 = 1;

    test_equal_b(compare(a1, length_a1, a2, length_a2), true);
    test_equal_b(compare(a1, length_a1, a2, 1), false);
    test_equal_b(compare(a1, 0, a2, length_a2), false);
    test_equal_b(compare(NULL, 0, NULL, 0), true);
    test_equal_b(compare(a3, 1, a2, 1), true);
    test_equal_b(compare(a3, length_a3, a2, length_a2), false);
    test_equal_b(compare(a3, 2, a2, 2), false);
    test_equal_b(compare(a1, -2, a2, 2), false);
    test_equal_b(compare(a1, -2, a2, -2), false);
    test_equal_b(compare(a1, -2, a2, -1), false);
    test_equal_b(compare(a1, 2, a2, -2), false);
    test_equal_b(compare(a4, length_a4, a4, length_a4), true);
    test_equal_b(compare(a1, 1, a4, length_a4), true);
    test_equal_b(compare(a1, length_a1, a4, length_a4), false);
    test_equal_b(compare(a4, length_a4, a5, length_a5), false);
}

void test_remove_negatives(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    int a1_expected[] = {1, 2, 3, 8, 9};

    int a2[] = {-1, -2, -3, -4, -8, 9};
    int length_a2 = 6;
    int a2_expected[] = {9};

    int a3[] = {-1, -2, -3, -4, -8, -9};
    int length_a3 = 6;
    int a3_expected[] = {};

    int new_length = remove_negatives(a1, length_a1);
    test_equal_i(new_length, 5);
    test_equal_b(compare(a1, new_length, a1_expected, 5), true);

    new_length = remove_negatives(a2, length_a2);
    test_equal_i(new_length, 1);
    test_equal_b(compare(a2, new_length, a2_expected, 1), true);

    new_length = remove_negatives(a3, length_a3);
    test_equal_i(new_length, 0);
    test_equal_b(compare(a3, new_length, a3_expected, 0), true);
}

void test_intersect(){
    int a1[] = {1, 2, 3, -4, 8, 9};
    int length_a1 = 6;
    
    int a2[] = {2, -2, 6, -4, -8, 10};
    int length_a2 = 6;
    
    int a2_a1_intersected[] = {2, -4};
    
    
    int a3[] = {1, 17, 3, 5, 9, 8};
    int length_a3 = 6;
    
    int a4[] = {1, 17, 3, 5, 9};
    int length_a4 = 5;
    
    int a3_a4_intersected[] = {1, 17, 3, 5, 9};
    
    
    int a5[] = {1, 3 , -18};
    int length_a5 = 3;
    
    int a6[] = {2, -3, -19};
      int length_a6 = 3;
    
    int a5_a6_intersected[] = {};
    
    BetterArray result = intersect(a1, length_a1, a2, length_a2);
    
    test_equal_i(result.length, 2);
    test_equal_b(compare(result.array, result.length, a2_a1_intersected, 2), true);
    
    result = intersect(a3, length_a3, a4, length_a4);
    
    test_equal_i(result.length, 5);
    test_equal_b(compare(result.array, result.length, a3_a4_intersected, 5), true);
    
    result = intersect(a5, length_a5, a6, length_a6);
    test_equal_i(result.length, 0);
    test_equal_b(compare(result.array, result.length, a5_a6_intersected, 0), true);
}

void test_merge_sorted(){
    int a1[] = {1, 2, 3, 4, 8, 9};
    int length_a1 = 6;
    
    int a2[] = {-2, -2, 6, 14, 15, 100};
    int length_a2 = 6;
    
    int a1_a2_merged[] = {-2, -2, 1, 2, 3, 4, 6, 8, 9, 14, 15, 100};
    
    int result[12];
    
    merge_sorted_arrays(a1, length_a1, a2, length_a2, result, 12);
    test_equal_b(compare(result, 12, a1_a2_merged, 12), true);
    

    int a3[] = {1};
    int length_a3 = 1;
    
    int a4[] = {15, 100};
    int length_a4 = 2;
    
    int a3_a4_merged[] = {1, 15, 100};
    
    int result2[3];
    
    merge_sorted_arrays(a3, length_a3, a4, length_a4, result2, 3);
    test_equal_b(compare(result2, 3, a3_a4_merged, 3), true);
    
    
    int a5[] = {1, 3, 17};
    int length_a5 = 3;
    
    int a6[] = {};
    int length_a6 = 0;
    
    int a5_a6_merged[] = {1, 3, 17};
    
    int result3[3];
    
    merge_sorted_arrays(a5, length_a5, a6, length_a6, result3, 3);
    test_equal_b(compare(result3, 3, a5_a6_merged, 3), true);
    
    int result4[3];
    
    merge_sorted_arrays(a6, length_a6, a5, length_a5, result4, 3);
    test_equal_b(compare(result4, 3, a5_a6_merged, 3), true);
    
    
}

int main(void) {
    test_compare();
    test_remove_negatives();
    test_intersect();
    test_merge_sorted();

    return 0;
}
