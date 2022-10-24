#ifndef _LIBDSC_UTILITY_H
#define _LIBDSC_UTILITY_H

#include <string.h> // For memmove()
#include <stddef.h> // For size_t

// The value pointed at by "pointer", interpreted as "type"
#define _GET_VALUE(pointer, type) (*(type *)(pointer))

// A functions that swaps the contents of 2 memory locations.
// Returns -1 for failure, 0 for succes.
int swap(void *p1, void *p2, size_t data_size);

#endif // _LIBDSC_UTILITY_H