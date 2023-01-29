/*
make compress && ./compress
*/
#include "base.h"

// compress the string 
String compress(String s) {
    require_not_null(s);

    // todo: implement

    // calculate the number of place
    if(strlen(s) == 0)return s;
    int newLenght = strlen(s);
    int count = 1;
    int stringCount = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] ==  s[i +   1] ){
            count++;
            //for count > 9 we need more place to alloc.
            if(count > 2){
                newLenght--;
                if(count > 9){
                    newLenght += 1;
                }
            }
        }else{
            count = 1;
        }
    }
    // create a new String with aloccated Place
    String newS = xmalloc(newLenght + 1);

    count = 1;
    for(int i = 0; i < strlen(s); i++){
        int temp = i;
        //end if we have terminit Byte
        if(s[i]== '\0')break;
        //if elememt doesnt repeat yourself then nothing changes
        if(!(s[i] == s[i + 1])){
            newS[stringCount] = s[i];
            stringCount++;
        }else{
            //caunt will be calculated
            for(int j = i; j < strlen(s); j++){
                if (s[j] == s[j + 1]){
                    count++;
            }else{
                break;
                }   
            }
            //if count is > 9 we have to input string with different way
            if(count > 9){
                newS[stringCount] = '0' + 9;
                newS[stringCount + 1] = s[temp];
                if(count - 9 == 1){
                    newS[stringCount + 2] = s[temp];
                    stringCount += 3;
                    i = temp + count - 1;
                    count = 1;
                }else{
                    newS[stringCount + 2] = '0' + (count - 9);
                    newS[stringCount + 3] = s[temp];
                    stringCount += 4;
                    i = temp + count - 1;
                    count = 1;
                }
                
            }else{
                //if count < 9 
                newS[stringCount] = '0' + count;
                newS[stringCount + 1] = s[temp];
                stringCount += 2;
                i = temp + count - 1;
                count = 1;
                }   
            }
       
    }

    for(int i = 0; i < strlen(newS);i++ ){
        if(newS[i] == '?')newS[i] = '\0';
    }

    return newS;
}

void test(void) {
    test_equal_s(compress(""), "");
    test_equal_s(compress("Sample String"), "Sample String");
    test_equal_s(compress("Hello World"), "He2lo World");
    test_equal_s(compress("AAAABBBBCCCC"), "4A4B4C");
    test_equal_s(compress("AAAAAAAAAAAA"), "9A3A");
    test_equal_s(compress("AAAAAAAAAA"), "9AA");
    test_equal_s(compress("BAAAAAAAAAAAAB"), "B9A3AB");
    test_equal_s(compress("BAAAAAAAAAAAABBBBBBBBBB"), "B9A3A9BB");
    test_equal_s(compress("FFFdddBBBBBBeeeEee"), "3F3d6B3eE2e");
}

int main(void) {
    test();
    return 0;
}