#ifndef __MULTISET_H__
#define __MULTISET_H__
#include "base.h"

// Function pointer types.
typedef int (*HashFun)(void*);
typedef bool (*EqualFun)(void* object1, void* object2);
typedef void (*FreeFun)(void* object);
typedef void* (*CopyFun)(void* object);

// Opaque type. Its attributes are not part of the interface.
typedef struct Multiset Multiset; 

// Creates a new multiset. n_buckets should be on the order of the expected 
// number of elements in the multiset. hash computes hash values of elements.
// equal compares two elements.
Multiset* new_multiset(int n_buckets, HashFun hash, EqualFun equal);

// Copy the multiset. Copy the elmenets if copy is not NULL.
Multiset* copy_multiset(Multiset* s, CopyFun copy);

// Check whether the multiset is empty.
bool is_empty_multiset(Multiset* s);

// Count the number of different elements in the multiset.
int elements_multiset(Multiset* s);

// Count the number of instances in the multiset.
int instances_multiset(Multiset* s);

// Count the number of instances of x.
int count_multiset(Multiset* s, void* x);

// Check whether x is contained in the multiset.
bool contains_multiset(Multiset* s, void* x);

// Add count instances of x to the multiset.
void add_multiset(Multiset* s, void* x, int count);

// Remove count instances of element from the multiset.
// Free the removed element if free_element is not NULL.
void remove_multiset(Multiset* s, void* element, int count, FreeFun free_element);

// Delete the multiset.
// Free the elements if free_element is not NULL.
void free_multiset(Multiset* s, FreeFun free_element);

//////////////////////////////////////////////////////////////
// Iterator

// Opaque type. Its attributes are not part of the interface.
typedef struct Iterator Iterator;

// Result type for the iterator. Holds the element and its number of occurences.
typedef struct PointerInt {
    void* p;
    int i;
} PointerInt;

// Create a new iterator for s.
Iterator* new_iterator(Multiset* s);

// Checker whether there are more elements to iterate.
bool has_next(Iterator* iter);

// Advance the iterator to and return the next element.
// If the iterator is expired then p == NULL.
PointerInt next(Iterator* iter);

// Free the iterator.
void free_iterator(Iterator* iter);

//////////////////////////////////////////////////////////////
// Set operations

// Intersection of a and b. Let c := intersect(a, b). Then for all x 
// count(c, x) = min(count(a, x), count(b, x)).
// Does not modify a or b. Creates a new result set. Does not copy the elements.
Multiset* intersection_multiset(Multiset* a, Multiset* b);

// Union of a and b. Let c := union(a, b). Then for all x 
// count(c, x) = max(count(a, x), count(b, x)).
// Does not modify a or b. Creates a new result set. Does not copy the elements.
Multiset* union_multiset(Multiset* a, Multiset* b);

// Sum of a and b. Let c := sum(a, b). Then for all x 
// count(c, x) = count(a, x) + count(b, x).
// Does not modify a or b. Creates a new result set. Does not copy the elements.
Multiset* sum_multiset(Multiset* a, Multiset* b);

#endif
