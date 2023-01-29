#include "base.h"



String  decToBin(int value){
    int count = 0;
    int tempval = value;
    while(true){
        if (tempval % 2 == 1)tempval--;
        tempval = tempval / 2;
        count++;
        if(tempval == 0)break;
    }

    char* output = xmalloc(count + 1);
    

    for(int i = count - 1  ; i >= 0; i--){
        if (value % 2 == 0){
            output[i] = '0';
            value = value / 2; 
        }else{
            output[i] = '1';
            value = (value - 1) / 2;
        }
    }
    output[count] = '\0';
    return output;
}


void test(void){
    test_equal_s(decToBin(2), "10");
    test_equal_s(decToBin(4), "100");
    test_equal_s(decToBin(5), "101");
    test_equal_s(decToBin(8), "1000");
    test_equal_s(decToBin(16), "10000");
    test_equal_s(decToBin(20), "10100");
}

int main(void){
    test();
    return 0;
}