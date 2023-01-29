/*
make merge_start && ./merge_start
*/

#include "base.h"

// Checks if s starts with prefix.
bool starts_with(String s, String prefix)
{
    require_not_null(s);
    require_not_null(prefix);
    while (*prefix)
    {
        if (*s != *prefix)
            return false;
        s++;
        prefix++;
    }
    return true;
}

// <purpose statement>
String merge_prefix(String *a, int n, String prefix)
{
    require_not_null(a);
    require("not negative", n >= 0);
    require_not_null(prefix);
    // implement 
    int alocsize = 0;
    int nrOfWords = 0;
    for(int i = 0; i < n ; i++){
        if(starts_with(a[i],prefix)){
            alocsize += strlen(a[i]);
            nrOfWords++;
        }
    }

    if(nrOfWords == 0)return "";
    printiln(alocsize + nrOfWords + 1 );
    String output = xmalloc((alocsize + nrOfWords + 1) * sizeof(char));
    int outputcount = 0;
    for(int i = 0; i < n ; i++){
        if(starts_with(a[i],prefix)){
            for(int j = 0; j < strlen(a[i]);j++){
                output[outputcount] = a[i][j];
                outputcount++;
            }
            output[outputcount] = ' ';
            outputcount++;
        }
    }
    output[outputcount] = '\0';
    return output;
}

void test(void)
{
    String a[] = {"abc", "xya", "abx", "xyz", "ab", "aKx"};
    int n = sizeof(a) / sizeof(char *);
    printiln(n);
    test_equal_s(merge_prefix(a, n, "ab"), "abc abx ab ");
    test_equal_s(merge_prefix(a, n, "xy"), "xya xyz ");
    test_equal_s(merge_prefix(a, n, ""), "abc xya abx xyz ab aKx ");
    test_equal_s(merge_prefix(a, n, "k"), "");
    test_equal_s(merge_prefix(a, n, "a"), "abc abx ab aKx ");
}

int main(void)
{
    test();
    return 0;
}