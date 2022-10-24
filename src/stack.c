#include "stack.h"

Stack *s_create(size_t data_size, void (*free_func)(void *))
{
    // Alloc memory for the stack, if it fails return NULL.
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;

    // Now the rest is easy.
    // Create the vector inside, if it fails clean up and return NULL.
    stack->vector = v_create(data_size, free_func);
    if (stack->vector == NULL) {
        free(stack);
        return NULL;
    }

    // Return the stack.
    return stack;
}

void st_free(Stack *stack)
{
    // Free the vector inside.
    v_free(stack->vector);

    // Free the stack struct.
    free(stack);
    stack = NULL;
}

int st_push(Stack *stack, void *data)
{
    return v_push_back(stack->vector, data);
}

void *st_pop(Stack *stack)
{
    return v_pop_back(stack->vector);
}