/*
Compile: make total-solution
Run: ./total-solution
make total-solution && ./total-solution
*/

#include "base.h"


//todo: define constants 
int Preis1 = 50;  //Preis ohne Rabatt
int Preis2 = 45;  //Preis ab 10 Schokoriegeln  
int Preis3 = 40; //Preis ab 100 Schokoriegeln 
int Versandpreis = 500;
int Grenze = 2000;


//todo: Write function total
int total(int Anzahl ) //Die Funktion übernimmt der Anzahl der Schokoriegeln und gibt zuruck, was man dafür bezahlen müss. (inklusiv  Versandkosten, wenn das der Fall ist)
//todo: Write function total_test
{
	int result = 0;
	if ( Anzahl <= 0){result = Anzahl * 0;
	} else { 
		if (Anzahl > 0 && Anzahl < 10){result = Anzahl * Preis1;

		} else {
		if (Anzahl >= 10  && Anzahl < 100){result = Anzahl * Preis2;
		}else{
			if (Anzahl >= 100){ result =  Anzahl * Preis3; 
            }
             } 
		}
	}
	if (result < Grenze  && result > 0){result += Versandpreis;
	} 
   return result;
}


void total_test (){

	//todo: call total_test Function
	test_equal_i(total(-2), 0);
    test_equal_i(total(0), 0);
    test_equal_i(total(2), 600);
    test_equal_i(total(10), 10 * 45 + 500);
    test_equal_i(total(100),100 * 40 );
    
}
int main(void){
    total_test();
    return 0;
}