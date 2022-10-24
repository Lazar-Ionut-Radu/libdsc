#include "queue.h"

Queue *q_create(size_t data_size, void (*free_func)(void *))
{
    // Alloc memory for the stack, if it fails return NULL.
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL)
        return NULL;

    // Now the rest is easy.
    // Create the vector inside, if it fails clean up and return NULL.
    queue->vector = v_create(data_size, free_func);
    if (queue->vector == NULL) {
        free(queue);
        return NULL;
    }

    // Return the stack.
    return queue;
}

int _q_is_allocated(Queue *queue)
{
    // Check if the queue is alloc'ed.
    if (queue == NULL)
        return -1;

    // Check if the vector inside is alloc'ed
    return _v_is_allocated(queue->vector);
}

int q_get_size(Queue *queue)
{
    // Return -1 if the queue is alloc'ed.
    if (_q_is_allocated(queue) == -1)
        return -1;

    // Otherwise return the size of the queue.
    return queue->vector->size;
}

void q_free(Queue *queue)
{
    // Free the vector inside.
    v_free(queue->vector);

    // Free the stack struct.
    free(queue);
    queue = NULL;
}

int q_push(Queue *queue, void *data)
{
    return v_push_front(queue->vector, data);
}

void *q_pop(Queue *queue)
{
    return v_pop_back(queue->vector);
}