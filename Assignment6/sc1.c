/*
Compile: make secret_message
Run: ./secret_message
*/

#include "base.h"
#include "string.h"

//todo: Write decode method
/* Die Funtion nimmt den String s und decodiert das Inhalt  zu ein anderen String
	@param s String.
    @return String, den decodierte Text von s .
*/
int s_length(String s); // Anzahl Zeichen in einem String
String s_copy(String s); // String s kopieren
char s_get(String s, int i); // Zeichen an Index i zurückgeben
void s_set(String s, int i, char c); // Zeichen an Position i auf c setzen

 String decode( String x ){
     String s = s_copy(x);
     int a;
     for (a = 0 ; a < s_length(s); a++){
         char d = s_get(s, a);
         if( (d >= 48 && d <= 57) || d == 32 || d == 46 || d == 58){ 
            s_set( s,a,d);   
            } else {
                 if (d > 64 && d < 91){
                    char c = d - 65;
                    d =  65 + 25 - c;
                    s_set( s,a,d);
                    } else {
                        char c = d - 97;
                        d = 97 + 25 - c;
                        s_set( s,a,d);
                        }
                    }
                }	
         return s;
     }
 
 
//todo: Write test method for decode
void test_decode(){
    test_equal_s(decode("AAA"), "ZZZ");
    test_equal_s(decode("ABC"), "ZYX");
    test_equal_s(decode("A B"), "Z Y");
    test_equal_s(decode("A .b"), "Z .y");
    test_equal_s(decode("A .b:"), "Z .y:");
  
}
/*
 int main(void){
    test_decode();
    return 0;
 }
 */
//todo: Write encode method
 String encode( String x ){
    String s = decode(x);
     return s; 
     }

void test_encode(){
     
    test_equal_s(encode("ZZZ"), "AAA");
    test_equal_s(encode("ZYX"), "ABC");
    test_equal_s(encode("Z Y"), "A B");
    test_equal_s(encode("Z .y"), "A .b");
    test_equal_s(encode("Z .y:"), "A .b:");
  
}
/*
 int  main(void){
    test_encode();
    return 0;
    }  
*/
//todo: Write test method for encode

int main(void){
	//todo: Decode this message to get a hint for part c) + d)
	String secret_message = "Kiltiznnrvivm 1 nzxsg Hkzhh. Wrvh rhg pvrmv Dviyfmt ufvi vgdzrtv Kilwfpgv zfu wvn Yrow. Grkk: Wrv Olvhfmt ufvi wzh vmxlwrvivm rhg tzma vrmuzxs fmw kzhhg rm vrmv Avrov.";
	
	printsln(decode(secret_message));
	printsln(encode(decode(secret_message)));
	
	//call test functions;

	return 0;
}
