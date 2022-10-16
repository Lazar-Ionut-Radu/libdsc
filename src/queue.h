#ifndef _LIBDSC_QUEUE_H
#define _LIBDSC_QUEUE_H

#include "vector.h"

// It's just a Vector with reduced functionality.
typedef struct Queue {
    Vector *vector;
} Queue;

// Creates a queue and returns a pointer to it.
// If it fails returns NULL.
Queue *q_create(size_t data_size, void (*free_func)(void *));

// Free's the memory of a queue.
void q_free(Queue *queue);

// Insert an element at the beginning of the queue.
// Returns 1 for succes, -1 for failure.
// If it fails the queue is left unchanged.
int q_push(Queue *queue, void *data);

// Removes the last element from the queue and returns a pointer to it.
// If it fails returns NULL and leaves the queue unchanged.
void *s_pop(Queue *queue);

#endif // _LIBDSC_QUEUE_H
