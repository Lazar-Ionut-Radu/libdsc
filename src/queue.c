#include "queue.h"

Queue *q_create(size_t data_size, void (*free_func)(void *))
{
    // Alloc memory for the stack, if it fails return NULL.
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL)
        return NULL;

    // Now the rest is easy.
    // Create the vector inside, if it fails clean up and return NULL.
    if (queue->vector = v_create(data_size, free_func) == NULL) {
        free(queue);
        return NULL;
    }

    // Return the stack.
    return queue;
}

void s_free(Queue *queue)
{
    // Free the vector inside.
    v_free(queue->vector);

    // Free the stack struct.
    v_free(queue);
    queue = NULL;
}

int s_push(Queue *queue, void *data)
{
    return v_push_front(queue->vector, data);
}

void *s_pop(Queue *queue)
{
    return v_pop_back(queue->vector);
}