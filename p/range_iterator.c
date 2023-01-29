/*
make range_iterator && ./range_iterator
*/

#include "base.h"

// Represents an inclusive or exclusive range.
typedef struct {
    int value; // the next value to return
    int end; // the end of the range
    int step; // must not be 0, must be >0 if start < end, must be <0 if start > end
    bool inclusive; // if this is an inclusive range, then end blongs to the range
} Range;

// Creates an exclusive range iterator, in which start is inclusive and end is exclusive. The first value is start, the second value is start + step, etc. Each value is in the interval [start, end) (if start <= end) or [end, start) (if start >= end). Step may be positive (if start <= end) or negative (if start >= end), but not zero.
Range make_exclusive_range(int start, int end, int step) {
    Range r = { 0, 0, 0, false };
    return r;
}

// Creates an inclusive range iterator, in which both start and end are inclusive. The first value is start, the second value is start + step, etc. Each value is in the interval [start, end] (if start <= end) or [end, start] (if start >= end). Step may be positive (if start <= end) or negative (if start >= end), but not zero.
Range make_inclusive_range(int start, int end, int step) {
    Range r = { 0, 0, 0, false };
    return r;
}

// Checks if r has another value to iterate.
bool has_next(Range* r) {
    return false;
}

// Returns the next value of the range.
int next(Range* r) {
    return 0;
}

int main(void) {
    Range r;

    r = make_exclusive_range(0, 8, 2);
    while (has_next(&r)) {
        int v = next(&r);
        printf("%d ", v);
    }
    println();

    r = make_inclusive_range(0, 8, 2);
    while (has_next(&r)) {
        int v = next(&r);
        printf("%d ", v);
    }
    println();

    r = make_exclusive_range(8, 0, -2);
    while (has_next(&r)) {
        int v = next(&r);
        printf("%d ", v);
    }
    println();

    r = make_inclusive_range(8, 0, -2);
    while (has_next(&r)) {
        int v = next(&r);
        printf("%d ", v);
    }
    println();

    r = make_exclusive_range(0, 8, 2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 0);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 4);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 6);
    test_equal_b(has_next(&r), false);

    r = make_inclusive_range(0, 8, 2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 0);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 4);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 6);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 8);
    test_equal_b(has_next(&r), false);

    r = make_exclusive_range(8, 0, -2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 8);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 6);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 4);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 2);
    test_equal_b(has_next(&r), false);

    r = make_inclusive_range(8, 0, -2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 8);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 6);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 4);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 2);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 0);
    test_equal_b(has_next(&r), false);

    r = make_exclusive_range(8, 8, 1);
    test_equal_b(has_next(&r), false);
    r = make_exclusive_range(8, 8, -1);
    test_equal_b(has_next(&r), false);
    r = make_inclusive_range(8, 8, 1);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 8);
    test_equal_b(has_next(&r), false);
    r = make_inclusive_range(8, 8, -1);
    test_equal_b(has_next(&r), true);
    test_equal_i(next(&r), 8);
    test_equal_b(has_next(&r), false);

    return 0;
}