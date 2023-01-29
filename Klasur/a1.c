#include "base.h"

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

char*remove_digits(char*s) {
    int b = 0;
    int a = 0;
    for(int j = 0; j < strlen(s); j++){
        if (is_digit(s[j]) == false){
            a++;
        }
    }
    char* rc = xmalloc(a );
    for(int i = 0; i < strlen(s); i++ ){
        if (is_digit(s[i]) == false){
            rc[b] = s[i];
            b++;
        }
    }
    rc[a ] = '\0';
    return rc;
}

void test(void) {
    test_equal_s(remove_digits(""), "");
    test_equal_s(remove_digits("x"), "x");
    test_equal_s(remove_digits("11"), "");
    test_equal_s(remove_digits("11x"), "x");
    test_equal_s(remove_digits("x11"), "x");
    test_equal_s(remove_digits("x11x"), "xx");
    test_equal_s(remove_digits("1a2b3c4"), "abc");
}

int main(void) {
    test();
    return 0;
}
