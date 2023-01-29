/*
Compile: make money
Run: ./money
make money && ./money
*/

#include "base.h"


const double BITCOIN_USD = 4273.38; // 1 Bitcoin = 4273.38 USD
const double EURO_USD = 1.14; 		// 1 EURO = 1.14 USD
const double DKK_USD = 0.15; 		// 1 Dansk Krone (DKK) = 0.15 USD


enum Currency { BITCOIN, DOLLAR, EURO, DANSK_KRONE }; 
typedef enum Currency Currency;

struct Money { double amount; Currency currency; }; 
typedef struct Money Money;

// double, Currency -> Money
// Initialize a Money structure.
Money make_money(double amount, Currency currency) {
    Money m = { amount, currency };
    return m;
}

// int Money, Money, double -> bool
// Test wheather the actual value of the money is within +/- tolerance of the expected value of the money.
bool test_value(int line, Money a, Money e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.currency, e.currency);
    return x && u;
}

void print_money(Money m);

void print_money_test() {
    print_money(make_money(1234, DOLLAR));
    print_money(make_money(1.234, BITCOIN));
    print_money(make_money(1.34, EURO));
    print_money(make_money(27.50, DANSK_KRONE)); 
}

// Money -> void
// Print the ammount of money.
void print_money(Money m) {
    // todo: implement
    if (m.currency == DOLLAR){
        printf ("%.2f $\n", m.amount);
        } else {
            if (m.currency == BITCOIN){
                printf ("%.8f Bitcoin\n", m.amount);
            } else {
                if (m.currency == EURO){
                printf ("%.2f Euro\n", m.amount);
                } else {
                    if (m.currency == DANSK_KRONE)
                    printf ("%.2f DKK\n", m.amount);
                    }
                }    
            }               
}

Money to_currency(Money m, Currency currency);

void to_currency_test(void) {
    test_value(__LINE__, to_currency(make_money(3, BITCOIN), DOLLAR), make_money(12820.14, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(6, DANSK_KRONE), EURO), make_money(0.789, EURO), 1e-3); 
    test_value(__LINE__, to_currency(make_money(20, EURO), DOLLAR), make_money(22.8, DOLLAR), 1e-3);
    test_value(__LINE__, to_currency(make_money(6, EURO), EURO), make_money(6, EURO), 1e-3);
    test_value(__LINE__, to_currency(make_money(3000, DOLLAR), BITCOIN), make_money(0.70202, BITCOIN), 1e-3);
    test_value(__LINE__, to_currency(make_money(25.25, DANSK_KRONE), EURO), make_money(3.32237, EURO), 1e-3);
    test_value(__LINE__, to_currency(make_money(87, BITCOIN), EURO), make_money(326126.36842105, EURO), 1e-3);
   
}

// Money, Currency -> Money
// Convert an amount of money to the given target currency.

Money to_currency(Money m, Currency target_currency) {
    // todo: implement
    switch (target_currency) {
        case DOLLAR:
            if (m.currency == EURO){
                m.amount = m.amount * EURO_USD;
                m.currency = DOLLAR;
                break;
                } else {
                    if (m.currency == BITCOIN) {
                        m.amount = m.amount * BITCOIN_USD;
                        m.currency = DOLLAR;
                        break;
                        } else {
                            if (m.currency == DANSK_KRONE) {
                                m.amount = m.amount * DKK_USD;
                                m.currency = DOLLAR;
                                break;
                                } else {
                                    break;
                                    }
                        }
                }   
                           
        case EURO:
            if (m.currency == DOLLAR){
                m.amount = m.amount / EURO_USD;
                m.currency = EURO;
                break;
                    } else {
                        if (m.currency == BITCOIN) {
                            m.amount = m.amount * BITCOIN_USD / EURO_USD;
                            m.currency = EURO;
                            break;
                            } else {
                                if (m.currency == DANSK_KRONE) {
                                m.amount = m.amount * DKK_USD / EURO_USD;
                                m.currency = EURO;
                                break;
                                } else {
                                    break;
                                }
                         }
                }

        case BITCOIN:
            if (m.currency == DOLLAR){
                m.amount = m.amount / BITCOIN_USD;
                m.currency = BITCOIN;
                break;
                    } else {
                        if (m.currency == EURO) {
                        m.amount = m.amount * EURO_USD / BITCOIN_USD;
                        m.currency = BITCOIN;
                        break;
                        } else { 
                            if (m.currency == DANSK_KRONE) {
                                m.amount = m.amount * DKK_USD / BITCOIN_USD;
                                m.currency = BITCOIN;
                                break;
                            } else {
                                break; 
                                }   
                        }
                }       
        
        case DANSK_KRONE:
            if (m.currency == DOLLAR){
                m.amount = m.amount / DKK_USD;
                m.currency = DANSK_KRONE;
                break;
            } else {
                if (m.currency == EURO) {
                    m.amount = m.amount * EURO_USD / DKK_USD;
                    m.currency = DANSK_KRONE;
                    break;
                    } else {
                         if (m.currency == BITCOIN) {
                            m.amount = m.amount * BITCOIN_USD / DKK_USD;
                            m.currency = DANSK_KRONE;
                            break;
                            } else {
                                break; 
                                }
                     }
                }

        default:
            return m;
    }
    // return make_money(1, EURO);
    return m;
}

int compare(Money m, Money v);

void compare_test(void) {
	test_equal_i(compare(make_money(1000, DOLLAR), make_money(877.19, EURO)), 0);
    // todo: add tests (at least 5)
    test_equal_i(compare(make_money(9, BITCOIN), make_money(100000, DANSK_KRONE)), 1);
    test_equal_i(compare(make_money(515, DOLLAR), make_money(1, BITCOIN)), -1);
    test_equal_i(compare(make_money(15, BITCOIN), make_money(15, BITCOIN)), 0);
    test_equal_i(compare(make_money(821, EURO), make_money(1300, DOLLAR)), -1);
    test_equal_i(compare(make_money(10.90, EURO), make_money(10.75, EURO)), 1);
}

    
// Money, Money -> int
// Compares two amounts of money. Returns 0 if the two amount of money are equal, 
// -1 if m is smaller than v and +1 otherwise.
int compare(Money m, Money v) {
    // todo: implement. May use the fabs function. fabs(double input) returns the absolute value of input.
    if ((int)lround(to_currency(m, EURO).amount * 100) > (int)lround(to_currency(v, EURO).amount * 100)){
        return 1;
        } else {
            if ((int)lround(to_currency(m, EURO).amount * 100) < (int)lround(to_currency(v, EURO).amount * 100)){
            return -1;
            } else {
                return 0;
                }
            }
        }
       

int main(void) {
    print_money_test();
    to_currency_test();
    compare_test();
    return 0;
}


