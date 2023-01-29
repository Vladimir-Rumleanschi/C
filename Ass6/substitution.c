#include "base.h"

const String permutation = "SGEMFVYZIDPBUKHARNXQWOLJTC";


//Die Funktion encrypt bekommt einen String und mit der Substitution der Chars in String, wird die Eingabe verschlüsselt und returned.
String encrypt(String input) {
    // TODO
    String tempinput = s_copy(input);

    for (int i = 0; i < strlen(tempinput); i++){   

        char tempchar = s_get(tempinput, i);
        if(tempchar > 90 || tempchar < 65){
            s_set(tempinput, i, tempchar);
        }else{
            int position = tempchar - 65;
            s_set(tempinput, i, permutation[position]);
        }
    }
    return tempinput;
}

int index_of(String s, char c) {
    for(int i = 0; i < s_length(s);i++){
        if(s[i] == c)return i;
    }
    return -1;
}
//Die Funktion encrypt bekommt einen String und mit der Substitution der Chars in String, wird die Eingabe zuruck verschlüsselt, so dass den String wieder lesbar ist.Lesbare String tempinput ist der Returnwert.
String decrypt(String input) {
    // TODO
    String tempinput = s_copy(input);
    for (int i = 0; i < strlen(tempinput); i++)
    {
        char tempchar = s_get(tempinput, i);
        if (tempchar > 90 || tempchar < 65){
            s_set(tempinput, i, tempchar);
        }
        else{
            int position = index_of(permutation, tempchar) + 1;
            s_set(tempinput, i, 64 + position);
        }
       
    }
    return tempinput;
}

void test_identity(String s) {
    assert("encrypted text must differ from input", !s_equals(s, encrypt(s)));
    test_equal_s(s, decrypt(encrypt(s)));
}

int main(void) {
    test_identity("H");
    test_identity("HELLO WORLD");
    test_identity("SOME SUPER SECRET TEXT");
    test_identity("DOES QUOTATION CAUSE ISSUES? IT SHOULDN'T.");
    test_identity("BE SURE TO DRINK YOUR OVALTINE");

    printsln("The secret text says:");
    printsln(decrypt("VNSKC DSYQ IU PHUABFQQ OFNLSZNBHXQFK QSJI RWFN MWNEZ GSTFNK."));
}
