#ifndef _LIBDSC_VECTOR_H
#define _LIBDSC_VECTOR_H

#include <stdlib.h> // For size_t.

// The capacity of the vector when it is created
#define INITIAL_CAPACITY 8

// Struct for a dynamically allocated array.
typedef struct Vector {
    // The number of elements in the vector.
    size_t size;

    // The number of elements allocated in the vector.
    size_t capacity;

    // The size of the elements in bytes.
    size_t data_size;

    // The dynamically allocated array.
    void **data;

    // Function that frees the memory of the elements.
    void (*free_func)(void *);
} Vector;

// Returns 0 if the vector is alloc'ed, -1 otherwise. 
int _v_is_allocated(Vector *vector);

// Doubles the capacity of the vector.
// Returns 0 for succes, -1 for failure.
// If it fails, the vector remains unchanged.
int _v_increase_capacity(Vector *vector);

// Halves the capacity of the vector.
// Returns 0 for succes, -1 for failure.
// If it fails, the vector remains unchanged.
int _v_decrease_capacity(Vector *vector);

// Insert an element at the given index.
// Returns 1 for succes, -1 for failure.
// If it fails the vector is left unchanged.
int v_insert(Vector *vector, void *data, size_t index);

// Insert an element at the end of the vector.
// Returns 1 for succes, -1 for failure.
// If it fails the vector is left unchanged.
int v_push_back(Vector *vector, void *data);

// Insert an element at the beginning of the vector.
// Returns 1 for succes, -1 for failure.
// If it fails the vector is left unchanged.
int v_push_front(Vector *vector, void *data);

// Removes an element from the vector and returns it.
// If it fails returns NULL and leaves the vector unchanged.
void *v_remove(Vector *vector, size_t index);

// Removes the last element from the vector and returns it.
// If it fails returns NULL and leaves the vector unchanged.
void *v_pop_back(Vector *vector);

// Removes the first element from the vector and returns it.
// If it fails returns NULL and leaves the vector unchanged.
void *v_pop_front(Vector *vector);

#endif // _LIBDSC_VECT0R_H
