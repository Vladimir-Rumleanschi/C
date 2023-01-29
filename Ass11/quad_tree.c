#define STBIW_ASSERT(x)
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "base.h"

// The maximum amount of elements a quad tree node can contain before splitting
// into more
const int MAX_ELEMENTS = 4;

// The maximum depth of the quad tree. The root node has a depth of 0. The
// depth of a node is equal to the depth of its parent incremented by 1.
const int MAX_DEPTH = 10;

// The bounds of the area represented by the quad tree.
const int WIDTH = 512;
const int HEIGHT = 512;

// This struct represents an element that is stored in the tree.
typedef struct element_s {
    double x, y;
} Element;

// A node of the quad tree.
typedef struct node_s {
    // The coordinates and size of the node.
    int x, y, w, h;
    // The node's depth.
    int depth;
    // Tagged union, store different data for leaf and non-leaf nodes.
    bool is_leaf;
    union {
        struct {
            // This node's children.
            struct node_s * tl, * tr, * bl, * br;
        } subtree;
        // The elements stored by this node.
        List elements;
    };
} Node;

Element new_element(double x, double y) {
    return (Element) {
        .x = x,
        .y = y
    };
}

Node * new_node(int x, int y, int width, int height, int depth) {
    Node * node = xmalloc(sizeof(Node));
    *node = (Node) {
        .x = x,
        .y = y,
        .w = width,
        .h = height,
        .depth = depth,
        .is_leaf = true,
        .elements = l_create(sizeof(Element)),
    };

    return node;
}

void free_node(Node * node) {
    // TODO
}

void insert_element(Node * node, Element e) {
    // TODO
}

void set_pixel(unsigned char * canvas, unsigned char r, unsigned char g, unsigned char b, int x, int y) {
    // TODO
}

void draw_node(Node * root, unsigned char * canvas) {
    // TODO
}

// This function generates a random, normally distributed value. Its mean value
// is the middle of min and max. It is ensured that the random value does not
// exceed min or max.
double random_coordinate(double min, double max) {
    double u1 = d_rnd(1.);
    double u2 = d_rnd(1.);
    double r = sqrt(-2.*log(u1))*cos(2.*3.14159*u2);

    double coordinate = (max - min) / 2. + r * 100.;
    if(coordinate < min) return min;
    if(coordinate > max) return max;
    else return coordinate;
}

int main(void) {
    report_memory_leaks(true);

    // Insert randomly placed nodes in the tree.
    Node * root = new_node(0, 0, WIDTH, HEIGHT, 0);
    for(int i = 0; i < 400; i++) {
        double x = random_coordinate(0, WIDTH);
        double y = random_coordinate(0, HEIGHT);
        insert_element(root, new_element(x, y));
    }

    // Allocate a canvas to draw onto with WIDTH * HEIGHT pixels with 3
    // components (red, green and blue) for each pixel.
    unsigned char * canvas = xmalloc(sizeof(unsigned char) * WIDTH * HEIGHT * 3);

    // Set every pixel on the canvas to white
    memset(canvas, 255, sizeof(unsigned char) * WIDTH * HEIGHT * 3);

    draw_node(root, canvas);

    // Create a PNG file from the data in the canvas
    // (you can view this in any image software you like)
    stbi_write_png("quad_tree.png", WIDTH, HEIGHT, 3, canvas, 0);

    free(canvas);
    free_node(root);
    return 0;
}
