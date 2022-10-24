#ifndef _LIBDSC_VECTOR_ALGORITHMS_H
#define _LIBDSC_VECTOR_ALGORITHMS_H

#include "vector.h"

// Binary search for the value "data" in the given vector.
// The compare function "cmp" returns 0 for equality
//                                    1 if the first parameter is greater
//                                   -1 if the second parameter is greater
int v_binary_search(Vector *vector, int (*cmp)(void *, void *), void *data);

// Sorts the vector using bubble sort.
// The compare function "cmp" returns 0 for equality
//                                    1 if the first parameter is greater
//                                   -1 if the second parameter is greater
void v_bubble_sort(Vector *vector, int (*cmp)(void *, void *));

// Sorts the vector using insertion sort.
// The compare function "cmp" returns 0 for equality
//                                    1 if the first parameter is greater
//                                   -1 if the second parameter is greater
void v_insertion_sort(Vector *vector, int (*cmp)(void *, void *));

int _v_qs_partition(Vector *vector, int (*cmp)(void *, void *), int low, int high);

// Sorts the vector [low, high] using quick sort.
// The compare function "cmp" returns 0 for equality
//                                    1 if the first parameter is greater
//                                   -1 if the second parameter is greater
void v_quick_sort(Vector *vector, int (*cmp)(void *, void *), int low, int high);

void _v_merge(Vector *vector, int (*cmp)(void *, void *), int left, int mid, int right);

// Sorts the vector [low, high] using merge sort.
// The compare function "cmp" returns 0 for equality
//                                    1 if the first parameter is greater
//                                   -1 if the second parameter is greater
void v_merge_sort(Vector *vector, int (*cmp)(void *, void *), int left, int right);

#endif // _LIBDSC_VECTOR_ALGORITHMS_H