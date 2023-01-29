/*
Compile: make multiset
Run: ./multiset
make multiset && ./multiset
*/

#include "multiset.h"

// A node in the overflow list.
typedef struct MultisetNode {
    void* element;
    int count;
    struct MultisetNode* next;
} MultisetNode;

// Construction function for a node.
MultisetNode* new_multiset_node(void* element, int count, MultisetNode* next) {
    MultisetNode* node = xcalloc(1, sizeof(MultisetNode));
    node->element = element;
    node->count = count;
    node->next = next;
    return node;
}

// Multiset data.
struct Multiset {
    int n_buckets; // number of buckets
    MultisetNode** buckets; // array of buckets, length n (each element is a pointer to an element)
    int n_elements; // number of different elements
    int n_instances; // number of instances
    HashFun hash; // computes hash value of elements
    EqualFun equal; // compares two elements
}; 

// Construction function for a multiset.
Multiset* new_multiset(int n_buckets, HashFun hash, EqualFun equal) {
    Multiset* s = xcalloc(1, sizeof(Multiset));
    s->n_buckets = n_buckets;
    s->buckets = xcalloc(n_buckets, sizeof(MultisetNode*));
    s->n_elements = 0;
    s->n_instances = 0;
    s->hash = hash;
    s->equal = equal;
    return s;
}

//////////////////////////////////////////////////////////////
// Iterator

struct Iterator {
    Multiset* s; // the multiset over which this iterator iterates
    int bucket_index; // current bucket list index
    MultisetNode* node; // current node in list
};

Iterator* new_iterator(Multiset* s) {
    Iterator* i = xcalloc(1, sizeof(Iterator));
    i->s = s;
    i->bucket_index = -1;
    i->node = NULL;
    return i;
}

bool has_next(Iterator* iter) { // does not change state of iterator
    if (iter->node != NULL && iter->node->next != NULL) { // in bucket list
        return true; // there is another node in this bucket list
    } else { // try next bucket lists
        Multiset* s = iter->s;
        for (int i = iter->bucket_index + 1; i < s->n_buckets; i++) {
            if (s->buckets[i] != NULL) return true; // bucket i is not empty
        }
    }
    return false; // no more elements
}

PointerInt next(Iterator* iter) { // modifies state of iterator
    PointerInt result = { NULL, 0 };
    if (iter->node != NULL && iter->node->next != NULL) {
        iter->node = iter->node->next; // advance iterator
        result.p = iter->node->element;
        result.i = iter->node->count;
    } else {
        Multiset* s = iter->s;
        for (int i = iter->bucket_index + 1; i < s->n_buckets; i++) {
            if (s->buckets[i] != NULL) {
                iter->bucket_index = i; 
                iter->node = s->buckets[i]; // advance iterator
                result.p = iter->node->element;
                result.i = iter->node->count;
                break;
            }
        }
    }
    return result; // no more nodes
}

void free_iterator(Iterator* iter) {
    free(iter);
}

//////////////////////////////////////////////////////////////

Multiset* copy_multiset(Multiset* s, CopyFun copy) {
    // todo: implement (c)
    return s;
}

bool is_empty_multiset(Multiset* s) { 
    return s->n_elements == 0; 
}

int elements_multiset(Multiset* s) { 
    return s->n_elements;
}

int instances_multiset(Multiset* s) { 
    return s->n_instances;
}

MultisetNode* find_multiset(Multiset* s, void* element) {
    // todo: implement (a)
    return NULL;
}

int count_multiset(Multiset* s, void* element) {
    MultisetNode* node = find_multiset(s, element);
    if (node == NULL) return 0;
    return node->count; 
}

bool contains_multiset(Multiset* s, void* element) {
    return find_multiset(s, element) != NULL;
}

void add_multiset(Multiset* s, void* element, int count) {
    // todo: implement (b)
}

void remove_multiset(Multiset* s, void* element, int count, FreeFun free_element) {
    // todo: implement (h, difficult)
}

void free_multiset(Multiset* s, FreeFun free_element) {
    // todo: implement (d)
}

//////////////////////////////////////////////////////////////

Multiset* intersection_multiset(Multiset* a, Multiset* b) {
    // todo: implement (e)
    return a;
} 

Multiset* union_multiset(Multiset* a, Multiset* b) {
    // todo: implement (f)
    return a;
} 

Multiset* sum_multiset(Multiset* a, Multiset* b) {
    // todo: implement (g)
    return a;
}

//////////////////////////////////////////////////////////////

int hash_string(void* x) {
    String element = x;
    int n = s_length(element);
    int hash = 0;
    for (int i = 0; i < n; i++) {
        hash = hash * 31 + element[i];
    }
    if (hash < 0) hash = -hash;
    return hash;
}

void* copy_string(void* s) {
    return s_copy(s);
}

void free_string(void* s) {
    free(s);
}

bool strings_equal(void* x, void* y) {
    return s_equals(x, y);
}

int main(void) {
    report_memory_leaks(true);
    
    Multiset* s = new_multiset(4, hash_string, strings_equal);
    printbln(is_empty_multiset(s));
    add_multiset(s, "a", 1);
    printbln(is_empty_multiset(s));
    add_multiset(s, "b", 2);
    add_multiset(s, "c", 3);
    add_multiset(s, "d", 4);
    printbln(contains_multiset(s, "a"));
    printbln(contains_multiset(s, "x"));
    remove_multiset(s, "d", 3, NULL);
    printf("elements = %d\n", elements_multiset(s));
    printf("instances = %d\n", instances_multiset(s));
    printf("count a = %d\n", count_multiset(s, "a"));
    printf("count b = %d\n", count_multiset(s, "b"));
    printf("count c = %d\n", count_multiset(s, "c"));
    printf("count d = %d\n", count_multiset(s, "d"));
    printf("count e = %d\n", count_multiset(s, "e"));
    
    // remove_multiset(s, "a", 300, NULL);

    printsln("s:");
    Iterator* iter = new_iterator(s);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    free(iter);
    
    Multiset* t = new_multiset(4, hash_string, strings_equal);
    add_multiset(t, "a", 3);
    add_multiset(t, "d", 5);
    add_multiset(t, "e", 1);
    
    printsln("t:");
    iter = new_iterator(t);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    free(iter);

    Multiset* r = intersection_multiset(s, t);
    printsln("r:");
    iter = new_iterator(r);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    free_multiset(r, NULL);
    free(iter);

    r = union_multiset(s, t);
    printsln("r:");
    iter = new_iterator(r);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    free_multiset(r, NULL);
    free(iter);

    r = sum_multiset(s, t);
    printsln("r:");
    iter = new_iterator(r);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    printf("r->n_instances = %d\n", r->n_instances);
    printf("r->n_elements = %d\n", r->n_elements);
    free_multiset(r, NULL);
    free(iter);
    
    r = copy_multiset(s, copy_string);
    printsln("r:");
    iter = new_iterator(r);
    while (has_next(iter)) {
        PointerInt pi = next(iter);
        printf("%s %d\n", pi.p, pi.i);
    }
    free_multiset(r, free_string);
    free(iter);

    free_multiset(t, NULL);
    free_multiset(s, NULL);
    return 0;
}
