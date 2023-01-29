#include "base.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

typedef enum typetag_e {
    CYLINDER,
    CUBOID,
    SPHERE,
} TypeTag;

typedef struct cylinder_s {
    double r, h;
} Cylinder;

typedef struct cuboid_s {
    double a, b, c;
} Cuboid;

typedef struct sphere_s {
    double r;
} Sphere;

typedef struct body_s {
    // todo
    enum typetag_e tag;

    union {
        struct cylinder_s cylinder;
        struct sphere_s sphere;
        struct cuboid_s cuboid;
    };
    
} Body;

/*todo: b) Die Enumeration Tag erleichtert die Arbeit mit mehrere Variablen,mit Hilfe von dieser Enumeration ist moeglich mehrere Variablen zu einen Tag zuweisen,
so dass am Ende das Code verstendlicher und "ästetischer" aussieht. Ausserdem man kann die Anweisung "switch" benutzen, was einen Statment durchführt wenn der Richtiger tag angegeben wird, ähnlich wie die if-Anweisung
*/

Body make_cylinder(double r, double h) {
    // todo
    require("radius must not be negative", r > 0)
    require("height must not be negative", h > 0)

    struct body_s body;

    body.tag = CYLINDER;
    body.cylinder.r = r;
    body.cylinder.h = h;

    return body;
}

Body make_cuboid(double a, double b, double c) {
    // todo
    require("lengthmust not be negative", a > 0)
    require("width must not be negative ", b > 0)
    require("height must not be negative", c > 0)

    struct body_s body;
    body.tag = CUBOID;
    body.cuboid.a = a;
    body.cuboid.b = b;
    body.cuboid.c = c;

    return body;
}

Body make_sphere(double r) {
    // todo
    require("radius must not be negative", r >= 0)

    struct body_s body;
    body.tag = SPHERE;
    body.sphere.r = r;

    return body;
}

double volume(Body body) {
    // todo
    double bodyVolume;
    switch (body.tag){

    case CYLINDER:
        require("gueltiger tag", body.tag == CYLINDER)
            bodyVolume = M_PI * body.cylinder.r * body.cylinder.r * body.cylinder.h;
        return bodyVolume;

    case SPHERE:
        require("gueltiger tag", body.tag == SPHERE)
            bodyVolume = 4 / 3.0 * M_PI * body.sphere.r * body.sphere.r * body.sphere.r;
        return bodyVolume;

    case CUBOID:
        require("gueltiger tag", body.tag == CUBOID)
            bodyVolume = body.cuboid.a * body.cuboid.b * body.cuboid.c;
        return bodyVolume;

        ensure("non-negative result", bodyVolume > 0)
    }
    return -1;
}

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}

int main(void) {
    volume_test();
    return 0;
}

