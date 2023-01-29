/*
Compile: make volume
Run: ./volume
make volume && ./volume
*/
#define _USE_MATH_DEFINES
#define _GNU_SOURCE
#include "base.h"

enum Tag { TCylinder, TSphere, TCuboid };
typedef enum Tag Tag;

struct Cylinder {
    double r, h; // V = pi * r^2 * h
};

struct Sphere {
    double r; // V = 4 / 3 * pi * r^3
};

struct Cuboid {
    double a, b, c; // V = a * b *c
};
struct GeomObject {
     // todo: implement
    enum Tag tag;
	
    union {
        struct Cylinder Cylinder;
        struct Sphere Sphere;
        struct Cuboid Cuboid;
    	};
	};

typedef struct Cylinder Cylinder;
typedef struct Sphere Sphere;
typedef struct Cuboid Cuboid;
typedef struct GeomObject GeomObject;

GeomObject make_cylinder(double r, double h) {
    // todo: implement
    require("non-negative radius", r >= 0);
    require("non-negative height", h >= 0);
	struct GeomObject o ;
	o.tag = TCylinder;
	o.Cylinder.r = r;
	o.Cylinder.h = h;
    
    return o;
}

GeomObject make_sphere(double r) {
    // todo: implement
    require("non-negative radius", r >= 0)
	struct GeomObject o ;
	o.tag = TSphere;
	o.Sphere.r = r;
    
    return o;
}

GeomObject make_cuboid(double a, double b, double c) {
     // todo: implement
    require("non-negative a length", a > 0)
    require("non-negative b width ", b > 0)
    require("non-negative c height", c > 0)
	struct GeomObject o ;
	o.tag = TCuboid;
	o.Cuboid.a = a;
	o.Cuboid.b = b;
	o.Cuboid.c = c;
    
    return o;
}

double volume(GeomObject o);

void volume_test(void) {
	test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    
}
    
// GeomObject -> double
// Computes the surface area of the given object.
double volume(GeomObject o) {
    // todo: implement
	
	double volume;
	switch(o.tag){
		
		case TCylinder:
		require("gueltiger tag", o.tag == TCylinder)
		volume =  M_PI * o.Cylinder.r * o.Cylinder.r * o.Cylinder.h;
		return volume;
		
		case TSphere:
		require("gueltiger tag", o.tag == TSphere)
		volume = 4 / 3.0 * M_PI * o.Sphere.r * o.Sphere.r * o.Sphere.r ;
		return volume;
		
		case TCuboid:
		require("gueltiger tag", o.tag == TCuboid)
		volume = o.Cuboid.a * o.Cuboid.b * o.Cuboid.c;
		return volume;
		
		ensure("non-negative result", volume > 0 )
	}
	return 0.0;
}

int main(void) {
    volume_test();
    return 0;
}

/*todo: d) Die Enumeration Tag erleichtert die Arbeit mit mehrere Variablen,
 mit Hilfe von dieser Enumeration ist moeglich mehrere Variablen zu einen Tag zuweisen,
so dass am Ende das Code verstendlicher und "ästetischer" aussieht. Ausserdem man kann die Anweisung switch
benutzen, was einen Statment durchführt wenn der Richtiger tag angegeben wird, ähnlich wie die if-Anweisung
*/