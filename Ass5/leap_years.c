#include "base.h" // prog1lib

//a)

int f(int i){
    printf("called f\n");
    if (i < 0){
        return -i;
    }else{
        return 3 * i;
    }  
}

// b) die Funkion überprüft ob angegebene Zahl kleiner 0 ist und gibt angegebene Zahl(i) als negativ zuruck, wenn aber es >= 0 dann wird i mit 3 multipliziert.
//    Ausserdem die Funktion printet einen String "called f\n"

//c)

const int numberOfLeapYear = 365;
const int numberOfNotLeapYear = 366;

/*
Return the number of days in the given year.
A leap year has 366 days, a non-leap year has 365 days.
The input represents any year A. D. as an integer, the return value is the num
ber of days.

*/
int numberOfDays(int year){

    bool multipleOfFour = year % 4 == 0;
    bool multipleOfHundread = year % 100 == 0;
    bool multipleOfFourhundred = year % 400 == 0;

    if(multipleOfFour || (multipleOfHundread && multipleOfFourhundred))return numberOfLeapYear;

    return numberOfNotLeapYear;

}

void numberOfDaysTest(){
    test_equal_i(numberOfDays(4), 365);
    test_equal_i(numberOfDays(100), 365);
    test_equal_i(numberOfDays(400), 365);
    test_equal_i(numberOfDays(123), 366);
}




int main(void){
    f(0);
    numberOfDaysTest();
    return 0;
}
