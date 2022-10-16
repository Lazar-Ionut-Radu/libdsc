#ifndef _LIBDSC_STACK_H
#define _LIBDSC_STACK_H

#include "vector.h"

// It's just a Vector with reduced functionality.
typedef struct Stack {
    Vector *vector;
} Stack;

// Creates a stack and returns a pointer to it.
// If it fails returns NULL.
Stack *s_create(size_t data_size, void (*free_func)(void *));

// Free's the memory of a stack.
void s_free(Stack *stack);

// Insert an element at the end of the stack.
// Returns 1 for succes, -1 for failure.
// If it fails the stack is left unchanged.
int s_push(Stack *stack, void *data);

// Removes the last element from the stack and returns a pointer to it.
// If it fails returns NULL and leaves the stack unchanged.
void *s_pop(Stack *stack);

#endif // _LIBDSC_STACK_H
