#include "base.h"

Mat. Nr: 10037218 Vladimir Rumleanschi 
Mat. Nr: 10014985 Hoang Phuong Tran

// Die Funktion erstellt die Quersummen der Digits einer Nummmer. Als Parameter hat man number was der Eingegebene Nummer ist und eine bool Variable, die besagt ob man eine normale
// Quersumme bestimmen muss oder eine alternierenden Quersumme. Als Rückgabe bekommt man die Quersumme bzw alternierenden Quersumme.
int digit_sum(unsigned number, bool alternating) {
    // TODO
    if(number / 10 < 1)return number;

    int numberOfDigits = 0;
    int tempnumber = number;
    
    while (tempnumber != 0 ){
        tempnumber = tempnumber / 10;
        numberOfDigits++;
    }

    int arrayOfDigits[numberOfDigits];
    int i = numberOfDigits - 1;

    while(number != 0){
        arrayOfDigits[i] = number % 10;
        number = number / 10;
        i--;
    }

    if(alternating){

        int alternatingQuersumme = 0;
        int check = 0;

        for (int i = 0; i < numberOfDigits; i++)
        {
            if(check == 0){
               
                alternatingQuersumme = alternatingQuersumme + arrayOfDigits[i];
                check = check + 1;
            }else{
                alternatingQuersumme = alternatingQuersumme - arrayOfDigits[i];
                check = check - 1;
            }
        
        }

        return alternatingQuersumme;

    }else{

       int quersumme = 0;

       for (int i = 0; i < numberOfDigits; i++)
       {
           quersumme = quersumme + arrayOfDigits[i];
       }
        return quersumme;
    }
    return 0;
}

bool divisible_by_eleven(unsigned number) {
    // TODO
    if (digit_sum(number, true) == 0)return true;
    if (digit_sum(number,true) > 10)return divisible_by_eleven(digit_sum(number, true));
    if (digit_sum(number, true) < 0) return divisible_by_eleven(number + 11);
    return false;
}

void digit_sum_test() {
    // TODO
    test_equal_i(digit_sum(10, false), 1);
    test_equal_i(digit_sum(333, false), 9);
    test_equal_i(digit_sum(333, true), 3);
    test_equal_i(digit_sum(5275, true), 5);
    test_equal_i(digit_sum(0, true), 0);
    test_equal_i(digit_sum(5, false), 5);
    test_equal_i(digit_sum(123123, true), 0);
    test_equal_i(digit_sum(123123, false), 12);

    // TODO
    test_equal_i(divisible_by_eleven(12), false);
    test_equal_i(divisible_by_eleven(11), true);
    test_equal_i(divisible_by_eleven(506), true);
    test_equal_i(divisible_by_eleven(5060506), true);
    test_equal_i(divisible_by_eleven(0), true);
    test_equal_i(divisible_by_eleven(5060507), false);
}

int main(void) {
    digit_sum_test();
    return 0;
}
