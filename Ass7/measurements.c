#include "base.h"

//Mat. Nr: 10037218 Vladimir Rumleanschi
//Mat. Nr: 10014985 Hoang Phuong Tran
typedef struct statistics_s {
    // todo
    int avAge;
    double standDev;
    double mTime;
    double tTime;
    double kTime;
} Statistics;

//function initialises the elements of the list with 0
Statistics make_statistics() {
    // todo
    Statistics list = {0,0.0,0.0,0.0,0.0};
    return list;
}
//function prints the elements of the list 
void print_statistics(Statistics s) {
    // todo
    printf("avarage age:\t\t\t %d years \n", s.avAge);
    printf("standard deviation of age:\t %f years\n", s.standDev);
    printf("avarage time with maus:\t\t %f s\n", s.mTime);
    printf("avarage time with touchscreen:\t %f s\n", s.tTime);
    printf("avarage time with keyboard:\t %f s\n", s.kTime);
}

Statistics compute_statistics(String table) {
    // todo
    Statistics statistics;
    statistics = make_statistics(statistics);

    int i = 0;

    int age = 0;
    
    int anzahl = 0;

    //loop calculate the sum of ages

    while(true){
        if (table[i] == '\n'){
            age += i_of_s(s_sub(table, i + 1, i + 3));
            anzahl++;
        }
        if (i + 2 == s_length(table))break;
        i++;
    }

    // average age
    statistics.avAge = round(age / anzahl);

    i = 13;
    int standDev = 0.0;

    //loop calculate the sum of standard deviation
    while (true){
        if (table[i] == '\n')standDev += ((i_of_s(s_sub(table, i + 1, i + 3)) - statistics.avAge) * (i_of_s(s_sub(table, i + 1, i + 3)) - statistics.avAge));
        if (i + 2 == s_length(table))break;
        i++;
    }

    //standard deviation
    statistics.standDev = sqrt(standDev/(anzahl - 1));

    i = 13;

    double mtime = 0.0;
    double ttime = 0.0;
    double ktime = 0.0;

    int nrOfMaus = 0;
    int nrOfTouchpad = 0;
    int nrOfKeyboard = 0;
    //loop calculate the sum of time of Keyboard, Maus and Touchscreen
    while (true){   
        if (table[i] == '\n'){
            if (table[i + 4] == 'm'){
                mtime += d_of_s(s_sub(table, i + 6, i + 13));
                nrOfMaus++;
            }else if (table[i + 4] == 't'){
                ttime += d_of_s(s_sub(table, i + 6, i + 13));
                nrOfTouchpad++;
            }else{
                ktime += d_of_s(s_sub(table, i + 6, i + 13));
                nrOfKeyboard++;
            }
        }
        if (i + 2 == s_length(table))
            break;
        i++;
    }

    //average time of Keyboard, Maus and Touchscreen
    statistics.mTime = mtime / nrOfMaus;
    statistics.tTime = ttime / nrOfTouchpad;
    statistics.kTime = ktime / nrOfKeyboard;

    return statistics;
}

int main(void) {
    String table = s_read_file("measurements.txt");
    Statistics statistics = compute_statistics(table);
    print_statistics(statistics);
    return 0;
}
