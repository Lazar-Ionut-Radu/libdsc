#include "utility.h"
#include <stdlib.h> // For malloc()

int swap(void *p1, void *p2, size_t data_size)
{
    // Alloc auxilary memory, return failure if it failed
    void *aux = malloc(data_size);
    if (aux == NULL)
        return -1;

    // Swap the elements.
    memmove(aux, p2, data_size);    
    memmove(p2, p1, data_size);
    memmove(p1, aux, data_size);
    
    // Return 0 for succes, free the auxilary memory.
    free(aux);
    return 0;
}