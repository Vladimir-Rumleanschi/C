#include "base.h"
/*
    make rects
    ./rects
    make rects && ./rects
*/

enum FillProperty{
    RANGE,
    SIMPLE,
    PATTERN
} typedef TFillProperty;

struct RangeFill{
    char start;
    char end;
} typedef RangeFill;

struct SimpleFill{
    char c;
} typedef SimpleFill;

struct PatternFill{
    String pattern;
} typedef PatternFill;

struct Fill{
    TFillProperty tag;
    union{
        PatternFill pf;
        SimpleFill sf;
        RangeFill rf;  
    };
}typedef Fill;

struct Rect{
    int x, y;
    int width, height;
    Fill fill;    
} typedef Rect;

void printcs(char c, int n) {
    for (int x = 0; x < n; x++) printc(c);
}

void printss(String c, int n) {
    for (int x = 0; x < n; x++) prints(c);
}


// Prints a row like this: +---+ (for n = 4), + (for n = 0), ++ (for n = 1), +-+ (for n = 2)
void print_outer_row(int width, int x) {
    // d) implement, using printc(char c) and println() and helper function printcs (above)
    for (int i = 0; i < x; i++) {
        printc(' ');
    }
    printc('+');
    printcs('-', width - 2);
    if (width > 1) {
        printc('+');
    }
    println();
}

// Prints a row like this: |   | (for n = 4), | (for n = 0), || (for n = 1), | | (for n = 2)
void print_inner_row(int width, int x, Fill fill) {
    // e) implement, using printc(char c) and println() and helper function printcs (above)
    switch (fill.tag) {
        case SIMPLE:
            for (int i = 0; i < x; i++) {
		    printc(' ');
            }
	        printc('|');
			printcs(fill.sf.c, width - 2);
            if (width > 1) {
		        printc('|');
	            }
            println();
			break;
		
        case PATTERN:
            for (int i = 0; i < x; i++) {
		        printc(' ');
                }
	        printc('|');
			printss(fill.pf.pattern, (width - 2) / s_length(fill.pf.pattern));
			for (int i = 0; i < (width - 2) % s_length(fill.pf.pattern) ; i++){
				printc (s_get (fill.pf.pattern, i));
                }
            if (width > 1) {
		        printc('|');
	            }
            println();
			break;
			
		case RANGE:	
            for (int i = 0; i < x; i++) {
		        printc(' ');
                }
	        printc('|');
			for (int i = 0; i < (width - 2) / (fill.rf.end - fill.rf.start + 1); i++){
				for (char i = fill.rf.start; i <= fill.rf.end; i++){
					printc(i);
				    }
			    }
			for (int i = 0; i < (width - 2) % (fill.rf.end - fill.rf.start + 1) ; i++){
				printc(fill.rf.start + i);
			    }
            if (width > 1) {
		        printc('|');
	            }
            println();
			break;
    }
}


Fill make_range_fill(char lower, char upper){
	require("valid input", lower <= upper && lower >= 1 && upper <= 127);
    Fill fill;
	fill.tag = RANGE;
	fill.rf.start = lower;
	fill.rf.end = upper;
    return fill;
}

Fill make_pattern_fill(String s){
    require("valid input", s_length(s) > 0);
    Fill fill;
    fill.tag = PATTERN;
    fill.pf.pattern = s;
    return fill;
}

Fill make_simple_fill(char c){
    require("valid input", isprint(c)!= 0 && c <= 127 && c >= 1);
    Fill fill;
	fill.tag = SIMPLE;
	fill.sf.c = c;
    return fill;
}

Rect make_rect(int x, int y, int width, int height, Fill fill){
    require(x >= 0, y >= 0);
    require(height >= 0, width >= 0);
	Rect rect;
	rect.x = x;
	rect.y = y;
	rect.width = width;
	rect.height = height;
	rect.fill = fill;

    return rect; 
}    

void draw_rect(Rect rect) {
	for(int i = 0; i < rect.y; i++){
		println();
	    }
	print_outer_row (rect.width, rect.x);
	for(int i = 0; i < rect.height - 2; i++ ){
		print_inner_row(rect.width, rect.x, rect.fill) ;
	    }   
	if (rect.height > 1) {
    print_outer_row (rect.width, rect.x);
        }	
}

/*
width = 1, height = 1
+

width = 1, height = 2
+
+

width = 2, height = 1
++

width = 2, height = 2
++
++

width = 3, height = 2
+-+
+-+

width = 3, height = 3, x = 1, y = 0, fill = simple with 'o'

 +-+
 |o|
 +-+
 
width = 15, height = 10, x = 15, y = 0, fill = pattern with ".o"
               +-------------+
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               |.o.o.o.o.o.o.|
               |o.o.o.o.o.o.o|
               +-------------+
*/
int main(void){
    // Mindestens 6 verschiedene Rechtecke mit unterschiedlichen Position, Fuellungen und Groeßen.
    draw_rect(make_rect(1, 1, 1, 1, make_simple_fill('o')));
    draw_rect(make_rect(2, 2, 2, 2, make_simple_fill('o')));
    draw_rect(make_rect(5, 5, 18, 9, make_range_fill('2','9')));
	draw_rect(make_rect(5, 11, 11, 11, make_pattern_fill("oOo")));
	draw_rect(make_rect(8, 12, 4, 6, make_simple_fill(' ')));
	draw_rect(make_rect(5, 8, 28, 10, make_pattern_fill("Programmieren macht Spass!")));
    return 0;
}