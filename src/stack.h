#ifndef _LIBDSC_STACK_H
#define _LIBDSC_STACK_H

#include "vector.h"

// It's just a Vector with reduced functionality.
typedef struct Stack {
    Vector *vector;
} Stack;

// Creates a stack and returns a pointer to it.
// If it fails returns NULL.
Stack *st_create(size_t data_size, void (*free_func)(void *));

// Returns 0 if the queue is alloc'ed, -1 otherwise. 
int _st_is_allocated(Stack *stack);

// Returns the size of the queue, or -1 if it is not alloc'ed
int st_get_size(Stack *stack);

// Free's the memory of a stack.
void st_free(Stack *stack);

// Insert an element at the end of the stack.
// Returns 1 for succes, -1 for failure.
// If it fails the stack is left unchanged.
int st_push(Stack *stack, void *data);

// Removes the last element from the stack and returns a pointer to it.
// If it fails returns NULL and leaves the stack unchanged.
void *st_pop(Stack *stack);

#endif // _LIBDSC_STACK_H
