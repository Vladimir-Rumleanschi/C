//Mat.Nr : 10037218 Vladimir Rumleanschi
//Mat.Nr : 10014985 Hoang Phuong Tran

/*
 * Compile:         make X
 * Run:             ./X
 * Compile and Run: make X && ./X
 */
#include "base.h" // prog1lib

    // todo: define constants
    const int normalPrice = 100;
const int smallSale = 90;
const int bigSale = 75;
const int smallRange = 10;
const int bigRange = 50;
const int deliveryPrice = 500;
const int deliveryRange = 2000;
// todo: write function price
int price(int nrOfItems){
    int totalprice = 0;
    //es wird überprüft mit welcher Konstante muss man die Anzahl der Items multiplizieren
    if(nrOfItems <= 0)return totalprice; 
    if(nrOfItems < smallRange)totalprice = nrOfItems * normalPrice;
    if(nrOfItems >= smallRange && nrOfItems < bigRange )totalprice = nrOfItems * smallSale;
    if(nrOfItems >= bigRange)totalprice = nrOfItems * bigSale;

    if(totalprice < deliveryRange)totalprice += deliveryPrice;// es wirdüberprüft ob man für den Versand bezahlen soll
    
    return totalprice;
}    
// todo: write function price_test
// test returned values of price using test_equal_i
void pricetest(){
    test_equal_i(price(0),0);
    test_equal_i(price(-1), 0);
    test_equal_i(price(5), 1000);
    test_equal_i(price(15), 1850);
    test_equal_i(price(22), 2480);
    test_equal_i(price(23), 2070);
    test_equal_i(price(52), 3900);
}

int main(void) {
    // todo: call price_test function
    pricetest();
    return 0;
}
