/*
    make base_converter
    ./base_converter
    make base_converter && ./base_converter
*/

#include "Base.h"

String characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//todo: write purpose statement inclusive @param and @return
/*Die Funktion rechnet die Länge des Zahl was in die neue Base dargestellt wird.
  @param number Zahl, Zahl in decimal dargestellt.
  @param base Zielbasis, in der die Zahl number dargestellt werden soll.
  @return Die Länge des gegebenen Zahl mit der zugehörigen Basis in w
*/
int length_for_base(int number, int base){
    if(number == 0)
        return 1;
    double needed_chars = log(number)/log(base);
    int length = ceil(needed_chars);
    if(length == (int)(needed_chars)){
        length++;
    }
    return length; 
}
/*
    Gibt einen dynamisch allokierte String zurueck, der so viele Zeichen hat wie noetig sind um die Zahl in der Zielbasis darzustellen. 
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
    @return Eine Zeichenkette mit der noetigen Anzahl an Stellen mit '#' initialisiert.
*/
String get_string_for_number_and_base(int number, int base){
    int length = length_for_base(number, base);
    String s = calloc(sizeof(char), length + 1);
    //printf("length: %d\n", length);
    for(int i = 0; i< length; i++){
        s[i] = '#';
    }
    return s;
}

/*
    Gibt die Zahl number in der Zielbasis als Zeichenkette zurueck.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
    @return String der die Zahl in der Zielbasis enthaelt.
*/
/*
int s_length(String s); // Anzahl Zeichen in einem String
void s_set(String s, int i, char c); // Zeichen an Position i auf c setzen
char s_get(String s, int i); // Zeichen an Index i zurückgeben
*/
String convert_to_base(int number, int base){
    String s = get_string_for_number_and_base(number, base);
    if (number == 0) {
        return "0";
    }
    if (base < 2 || base > 36) {
        return "";
        }
    while (number){
        int length = length_for_base (number, base);
        int rest;
        int i;
        for (i = length - 1 ; i >= 0 ; i--) {
            rest = number % base;
            number = number / base;
            s_set(s, i, s_get(characters, rest));
            }
        }
    return s;
}

/*
    Schoen formatierte Ausgabe der Zahl, die zu konvertieren ist, sowie des Ergebnisses.
    @param number Zahl, die in der Zielbasis dargestellt wird.
    @param base Zielbasis, in der die Zahl number dargestellt werden soll.  
*/
void print_convert(int number, int base){
    printf("Convert %4d to base %2d: %s\n", number, base, convert_to_base(number, base));
}
/*
    Testfaelle fuer convert_to_base.
*/
void test_convert_to_base(){
    print_convert(16, -1);
    test_equal_s(convert_to_base(16, -1), "");
    
    print_convert(10, 1);
    test_equal_s(convert_to_base(10, 1), "");
    
    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");
    
    print_convert(16, 3);
    test_equal_s(convert_to_base(16, 3), "121");
    
    print_convert(16, 16);
    test_equal_s(convert_to_base(16, 16), "10");
    
    print_convert(100, 10);
    test_equal_s(convert_to_base(100, 10), "100");
    
    print_convert(0, 2);
    test_equal_s(convert_to_base(0, 2), "0");
    
    print_convert(10, 16);
    test_equal_s(convert_to_base(10, 16), "A");
    
    print_convert(100, 2);
    test_equal_s(convert_to_base(100, 2), "1100100");
    
    print_convert(20, 5);
    test_equal_s(convert_to_base(20, 5), "40");
    
    print_convert(1300300300, 36);
    test_equal_s(convert_to_base(1300300300, 36), "LI5Y4S");
}


void print_bits(int number){
    String bits = convert_to_base(number, 2);
    printf("0x%4x : %16s\n", number, bits);
}

void bit_operations(){
    printsln("Bitmagic");
    //what does the following?
    printsln("&"); // & : jedes corespondierende bit wird vergleicht und durch UND verknüpft Z.b (0111 & 1010 to 0010)
    int a = 0xaf;
    int b = 0xa5;
    
    int c = a & b; 
    print_bits(a);
    print_bits(b);
    print_bits(c);
    
    printsln("|"); // | : jedes corespondierende bit wird vergleicht und durch inclusive OR verknüpft Z.b (0111 & 1010 to 1111)
    a = 0xb1;
    b = 0x93;
    c = a | b;
    print_bits(a);
    print_bits(b);
    print_bits(c);
    
    printsln("^"); // ^ : jedes corespondierende bit wird vergleicht und durch exclusive OR verknüpft Z.b (0111 & 1010 to 1101)
    a = 0xb1;
    b = 0x33;
    c = a ^ b;
    print_bits(a);
    print_bits(b);
    print_bits(c);
    
    printsln("<< und >>"); // << :  Verschibt die bits nach links (Z.b 0011 to 1100); >> : Verschibt die bits nach rechts (Z.b. 1100 to 0011)
    a = 0x30;
    print_bits(a);
    a <<= 2;
    print_bits(a);
    a >>= 3;
    print_bits(a);
    
}

//todo
int set_bit(int value, int index, bool bit){
   int a = 1 << index;
	if (bit){
		value = value | a;
	    } else {
		    value = value & ~a;
	        }
    return value;
    }

//todo
bool get_bit(int value, int index ){
    int a = value >> index;
	a = a << 31;
	return (a != 0);
    }

/*
    Testfaelle fuer get_bit und set_bit
*/
void test_get_set_bit(){
    int a = 0x77;
    //print_bits(a);
    
    test_equal_b(get_bit(a,0), true);
    test_equal_b(get_bit(a,1), true);
    test_equal_b(get_bit(a,2), true);
    test_equal_b(get_bit(a,3), false);
    test_equal_b(get_bit(a,4), true);
    test_equal_b(get_bit(a,5), true);
    test_equal_b(get_bit(a,6), true);
    test_equal_b(get_bit(a,7), false);
    test_equal_b(get_bit(a,8), false);
    
    a = set_bit(a, 0, false);
    test_equal_i(a, 0x76);
    a = set_bit(a, 0, true);
    test_equal_i(a, 0x77);
    a = set_bit(a, 5, false);
    test_equal_i(a, 0x57);
    a = set_bit(a, 1, true);
    test_equal_i(a, 0x57);
    a = set_bit(a, 3, false);
    test_equal_i(a, 0x57);
}

//todo
int extract_bits(int value, int start, int end){
    if (start < 0){
        return 0;
        }
    if (end > 31){
        return 0;
        }
    if (start >= end){
        return 0;
    }   
	value = value << (32 - end);
	value = value >> (32 - end + start);
    

    return value;
}

/*
    Testfaelle fuer extract_bits.
*/
void test_extract_bits(){
    test_equal_s(convert_to_base(extract_bits(0x1805, 0, 4),2), "101");
    test_equal_s(convert_to_base(extract_bits(0x1404, 8, 16),2), "10100");
    test_equal_s(convert_to_base(extract_bits(0x1701, 12, 16),2), "1");
    test_equal_s(convert_to_base(extract_bits(0x1602, 0, 16),2), "1011000000010");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 16, 0),2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, -1, 3),2), "0");
    test_equal_s(convert_to_base(extract_bits(0xABCD, 4, 34),2), "0");
}

int main(void){
    test_convert_to_base();
    test_get_set_bit();
    test_extract_bits();
    
    return 0;
}