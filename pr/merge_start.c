/*
make merge_start && ./merge_start
*/

#include "base.h"

// Checks if s starts with prefix.
bool starts_with(String s, String prefix) {
    require_not_null(s);
    require_not_null(prefix);
    while (*prefix) {
        if (*s != *prefix) return false;
        s++;
        prefix++;
    }
    return true;
}

// Gibt einen String zuruck was die Strings mit gegebenen Prefix haben
String merge_prefix(String* a, int n, String prefix) {
    require_not_null(a);
    require("not negative", n >= 0);
    require_not_null(prefix);
    // implement
    int j = 0;
    for(int i = 0; i < n; i++){
        if(starts_with(a[i],prefix)){
            j = strlen(a[i])+ 1;
        }
    }
    String s = xcalloc(j,sizeof(char));
    int len = 0;
    for(int i = 0; i < n; i++){
        if(starts_with(a[i],prefix)){
            for(int x = 0; x < strlen(a[i]);x++){
                s[len] = a[i][x];
                len++;
            }
            len++;
            s[len]  = ' ';
            len++;
        }
    }
    

    return s;
}

void test(void) {
    String a[] = { "abc", "xya", "abx", "xyz", "ab", "aKx" };
    int n = sizeof(a) / sizeof(char*);
    printiln(n);
    test_equal_s(merge_prefix(a, n, "ab"), "abc abx ab ");
    test_equal_s(merge_prefix(a, n, "xy"), "xya xyz ");
    test_equal_s(merge_prefix(a, n, ""), "abc xya abx xyz ab aKx ");
    test_equal_s(merge_prefix(a, n, "k"), "");
    test_equal_s(merge_prefix(a, n, "a"), "abc abx ab aKx ");
}

int main(void) {
    test();
    return 0;
}