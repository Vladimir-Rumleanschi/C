/*
Compile: make secret_message
Run: ./secret_message
*/

#include "base.h"

//todo: Write decode method
/* Die Funtion nimmt den String s und decodiert das Inhalt  zu ein anderen String
	@param s String.
    @return String, den decodierte Text von s .
*/
int s_length(String s); // Anzahl Zeichen in einem String
String s_copy(String s); // String s kopieren
char s_get(String s, int i); // Zeichen an Index i zurückgeben
void s_set(String s, int i, char c); // Zeichen an Position i auf c setzen

 String decode( String s ){
     int a;
     char Z = Z;
     
    for (a = 0; a < s_length(s); ++a ){
        char d = s_get(s, a);
        if ( d == 'A'){
		d = Z;
		s_set( s,a,d);
        }
    }	
    return s;
 }
 
//todo: Write test method for decode
void test_decode(){
    test_equal_s(decode("A"), "Z");
  
}
 int   main(){
    test_decode();
    return 0;
//todo: Write encode method

//todo: Write test method for encode

//int main(void){
	//todo: Decode this message to get a hint for part c) + d)
	//String secret_message = "Kiltiznnrvivm 1 nzxsg Hkzhh. Wrvh rhg pvrmv Dviyfmt ufvi vgdzrtv Kilwfpgv zfu wvn Yrow. Grkk: Wrv Olvhfmt ufvi wzh vmxlwrvivm rhg tzma vrmuzxs fmw kzhhg rm vrmv Avrov.";
	
	//printsln(decode(secret_message));
	//printsln(encode(decode(secret_message)));
	
	//call test functions

//	return 0;
}