/*
Compile: make four_sorted_digits
Run: ./four_sorted_digits
Compile and run:
make four_sorted_digits && ./four_sorted_digits
*/

#include "base.h"

// Purpose statement.
bool four_sorted_digits(String s)
{
    // todo: implement
    bool outputVal = false;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] > 47 && s[i] < 58){
            int digitCount = 1;
            if(i + 3 == strlen(s))break;
            for(int j = i + 1; j < i + 4; j++){
                if(!((s[j] > 47 && s[j] < 58 ) && ( s[j] >= s[j - 1] )))break;
                digitCount++;
            }
            if(digitCount ==  4){
                outputVal = true;
                break;
            }
        }  
    }
    return outputVal;
}

void four_sorted_digits_test(void)
{
    test_equal_b(four_sorted_digits(""), false);
    test_equal_b(four_sorted_digits("123"), false);
    test_equal_b(four_sorted_digits("abcd"), false);
    test_equal_b(four_sorted_digits("1234"), true);
    test_equal_b(four_sorted_digits("2479"), true);
    test_equal_b(four_sorted_digits("1111"), true);
    test_equal_b(four_sorted_digits("a123"), false);
    test_equal_b(four_sorted_digits("123a"), false);
    test_equal_b(four_sorted_digits("1234a"), true);
    test_equal_b(four_sorted_digits("xx1234y"), true);
    test_equal_b(four_sorted_digits("abc12345"), true);
    test_equal_b(four_sorted_digits("a 1 2 3 4 c"), false);
    test_equal_b(four_sorted_digits("a 3333 c"), true);
}

int main(void)
{
    report_memory_leaks(true);
    four_sorted_digits_test();
    return 0;
}