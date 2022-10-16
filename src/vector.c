#include "vector.h"
#include <stdio.h>
#include <string.h>

Vector *v_create(size_t data_size, void (*free_func)(void *))
{
    // Alloc memory for the vector.
    Vector *vector = malloc(sizeof(Vector));

    // If malloc() fails return NULL.
    if (vector == NULL)
        return NULL;

    // Initialize the variables inside a vector.
    vector->data_size = data_size;
    vector->size = 0;
    vector->capacity = INITIAL_CAPACITY;
    vector->free_func = free_func;

    // Alloc memory for the array.
    // If malloc() fails clean up and return NULL.
    vector->data = malloc(sizeof(void *) * vector->capacity);
    if (vector->data == NULL) {
        free(vector);
        return NULL;
    } 

    return vector;
}

void v_free(Vector *vector) 
{
    // Free the elements of the vector.
    for (size_t i = 0; i < vector->size; i++)
        (vector->free_func)(vector->data[i]);

    // Free the array inside the vector.
    free(vector->data);

    // Free the vector struct.
    free(vector);
    vector = NULL;
}

int _v_is_allocated(Vector *vector)
{
    // Return -1 if the vector is not alloc'ed
    if (vector == NULL)
        return -1;
    if (vector->data == NULL)
        return -1;

    // Return 0 if it is.
    return 0;
}

int _v_increase_capacity(Vector *vector) 
{
    // Return -1 for failure if the vector is not alloc'ed.
    if (_v_is_allocated(vector) == -1)
        return -1;

    // Realloc's the memory and returns -1 if it failed.
    void *copy_data = realloc(vector->data, sizeof(void *) * vector->capacity * 2);
    if (copy_data == NULL) {
        return -1;
    }
    vector->data = copy_data;

    // Increase the capacity.
    vector->capacity = 2 * vector->capacity;

    // Return 0 for succes.
    return 0;
}

int _v_decrease_capacity(Vector *vector)
{
    // Return -1 for failure if the vector is not alloc'ed.
    if (_v_is_allocated(vector) == -1)
        return -1;

    // If decreasing the capacity would affect elements in the vector return -1
    if (vector->size > vector->capacity / 2)   
        return -1;

    // Realloc's the memory and returns -1 if it failed.
    void *copy_data = realloc(vector->data, sizeof(void *) * vector->capacity / 2);
    if (copy_data == NULL) {
        return -1;
    }
    vector->data = copy_data;

    // Increase the capacity.
    vector->capacity = vector->capacity / 2;

    // Return 0 for succes.
    return 0;    
}

int v_insert(Vector *vector, void *data, size_t index)
{
    // Return -1 for failure if the vector is not alloc'ed.
    if (_v_is_allocated(vector) == -1)
        return -1;

    // Return -1 if the index is invalid.
    if (index > vector->size)
        return -1;

    // Alloc memory if it is needed.
    if (vector->size == vector->capacity) {
        // Increase the capacity; If it fails return -1.
        if (_v_increase_capacity(vector) == -1)
            return -1;
    }

    // Alloc memory for the new element. Undo changes to vector if it failes 
    // and return -1.
    void *new_element = malloc(vector->data_size);
    if (new_element == NULL) {
        _v_decrease_capacity(vector);
        return -1;
    }

    // Make space for the new element.
    for (size_t i = vector->size; i > index; i--) {
        vector->data[i] = vector->data[i-1];
    }

    // Insert the new element and increase the size.
    vector->data[index] = new_element;
    memmove(vector->data[index], data, vector->data_size);
    vector->size++;

    return 0;
}

int v_push_back(Vector *vector, void *data)
{
    return v_insert(vector, data, vector->size);
}

int v_push_front(Vector *vector, void *data)
{
    return v_insert(vector, data, 0);
}

void *v_remove(Vector *vector, size_t index)
{
    // Return -1 for failure if the vector is not alloc'ed.
    if (_v_is_allocated(vector) == -1)
        return NULL;

    // Return -1 if the index is invalid.
    if (index >= vector->size)
        return NULL;

    // Get the removed element.
    void *removed_element = vector->data[index];

    // Move the other elements over it.
    for (size_t i = index + 1; i < vector->size; i++) {
        vector->data[i - 1] = vector->data[i];
    }

    // Decrease the size.
    vector->size--;

    // Decrease the capacity if needed.
    if (vector->size <= vector->capacity / 2) 
        _v_decrease_capacity(vector);

    // Return the removed element.
    return removed_element;
}

void *v_pop_back(Vector *vector)
{
    return v_remove(vector, vector->size - 1);
}

void *v_pop_front(Vector *vector)
{
    return v_remove(vector, 0);
}
