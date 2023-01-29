/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"
#include <math.h>

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;

struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}


// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}

//end of template code

//now it is your turn ... 

// (a) todo: implement compare function
int compare(Car car1, Car car2){
	if(car1.year < car2.year){ 
		return 1;
		} else {
			if(car1.year > car2.year){
				return -1;
					} else {
						return strcmp(car1.brand, car2.brand);
						}
				}	
}

// (b) todo: write compare test function
void compare_test(void){
	Car car1 = {"VW", 2015, 10000, 10000.0};
	Car car2 = {"VW", 2020, 10000, 10000.0};
	test_equal_i(compare(car1,car2), 1);

	car1.year = 2021;
	test_equal_i(compare(car1,car2), -1);
	
	car2.year = 2021;
	test_equal_i(compare(car1,car2), 0);

	car1.brand = "Audi";
	test_equal_i(compare(car1,car2), -1);

	car2.brand = "Fiat";
	test_equal_i(compare(car1,car2), -1);
}

// (c) todo: implement sorted function
bool sorted(Car* a, int length){
	for(int i = 0; i < length - 1; i++){
		if(compare(a[i], a[i+1]) > 0) return false;
	}
	return true;
}

//randomly sorts an array return the number of swaps
int random_sort(Car* a, int length) {
	int swaps = 0;
	while(sorted(a, length) == false){ 
		int i1 = i_rnd(length);
		int i2 = i_rnd(length);
		Car temp = a[i1];
		a[i1] = a[i2];
		a[i2] = temp;
		swaps++; 
	}
	return swaps;
}

int main(void) {
	
	// (b) todo: test compare function
	compare_test();
	
	int number_of_random_cars = 10;
	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sortierung findet statt...\n");
	
	//todo: sort the car_park array.
	random_sort(car_park, 10);

	print_car_array(car_park, number_of_random_cars);

	delete_car_park(car_park);
	
	// (f) todo: compare the number of swaps and compare calls.
	for(int i = 3; i < 9; i++){
		int st = 0;
		
		for(int id = 0; id < 100; id++){
			Car* car_park = create_car_park(i);
			int swaps = random_sort(car_park, i);
			st = st + swaps;
		}
		double compares_mean = (double)((st + 1) * (i - 1)) / 100.0;

		double sm = (double) st / 100.0;
		printf("Es wird 100 Autos auf die Laenge %d sortiert, genommen %.2f swaps und %.2f vergleicht in die Range\n", i, sm, compares_mean);
	}
	
    return 0;
}
