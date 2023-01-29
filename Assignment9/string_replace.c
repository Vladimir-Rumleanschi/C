/*
    make string_replace
    ./string_replace
    make string_replace && ./string_replace
*/
#include "base.h"


char* next_occurence(char* s, char* find) {
    while (*s) {
        char* string = s;
        char* findvar = find;
        while (*s && *findvar && *s == *findvar) {
            s = s + 1;
            findvar = findvar + 1;
        }
        if (!*findvar) {
            return string;
        }
        s++;
    }
    return NULL;
}


void test_next_occurence() {
    test_equal_s(next_occurence("aabbccdd", "aa"), "aabbccdd");
    test_equal_b(next_occurence("abbccdd", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa") == NULL, true);
    test_equal_s(next_occurence("abbccdda", "a"), "abbccdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye") == NULL, true);
}

int count(char* s, char* find) {
    //todo:
    int k = 0;
    int a = 0;
        for (k = 0 ; k < strlen(s); k++) {
        if(next_occurence(&s[k],find) == &s[k]){
            a++;
        }
        }
        return a;        
    }
void test_count() {
    test_equal_i(count("aabbccdd", "aa"), 1);
    test_equal_i(count("abbccdda", "aa"), 0);
    test_equal_i(count("aabbaadd", "aa"), 2);
    test_equal_i(count("aabbccdd", "a"), 2);
    test_equal_i(count("aabbccdd", "abbc"), 1);
    test_equal_i(count("Die Uhrzeit ist 3:10", "Uhrzeit"), 1);
    test_equal_i(count("hello, hello world", "hello"), 2);
    test_equal_i(count("hello, hello world", "lo"), 2);
}

char* replace(char* s, char* find, char* replace_by) {
    int b = count(s, find);
    char *a = malloc((strlen(s) - xb *  strlen(find) + b * strlen(replace_by) ) * sizeof(char));
    if( next_occurence(s, find) == NULL ){
        for (int i = 0 ; i < strlen(s); i++)
        {
            if (s[i] == '?'){
                s[i] = '\0';
            }
        }
        return s;
    } else {
        char *c = next_occurence(s, find);
        int d = strlen(s) - strlen(c);
        int e = 0;
        for (int i = 0; i < d; i++) 
        {
            a[e] = s[i];
            e++;
        }
        for (int f = 0; f < strlen(replace_by); f++) 
        {
            a[e] = replace_by[f];
            e++;
        }
        for (int g = strlen(find); g < strlen(c); g++)
         {
            a[e] = c[g];
            e++;
        }
        s = a; 
        return replace(s, find, replace_by);
    }

}

void test_replace(){
    test_equal_s(replace("aabbccdd", "a", "d"), "ddbbccdd");
    test_equal_s(replace("aaabbccdd", "aa", "d"), "dabbccdd");
    test_equal_s(replace("aabbccdd", "aa", "d"), "dbbccdd");
    test_equal_s(replace("aabbccdd", "b", "olo"), "aaolooloccdd");
    test_equal_s(replace("aabbccdd", "c", ""), "aabbdd");
    test_equal_s(replace("hello, hello world", "hello", "bye"), "bye, bye world");
    test_equal_s(replace("aabbccdd", "dd", "eee"), "aabbcceee");
    test_equal_s(replace("for(int x = X; x < X * 3; x++){printiln(x);}", "X", "90"), "for(int x = 90; x < 90 * 3; x++){printiln(x);}");
}

int main(void){
    test_next_occurence();
    test_count();
    test_replace();
    return 0;
}
    