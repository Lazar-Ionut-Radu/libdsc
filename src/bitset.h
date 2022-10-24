#ifndef _LIBDSC_BITSET_H
#define _LIBDSC_BITSET_H

#include <stdlib.h> // For size_t.

// Statically allocated array of bits.
typedef struct Bitset {
    // The number of bits in the bitset.
    size_t size;

    // Array of bytes.
    char *bytes;
} Bitset;

// Creates and returns a pointer to a bitset.
// Returns NULL in case of failure. 
Bitset *bs_create(size_t size);

// Returns 0 if the bitset is alloc'ed, -1 otherwise.
int _bs_is_allocated(Bitset *bitset);

// Free's the memory of a bitset.
void bs_free(Bitset *bitset);

// 8bit ints with only 1 bit set to 1 
const char bits[8] = {1, 2, 4, 8, 16, 32, 64, 128};

// Sets the bit at index "index" to value "value".
// Return -1 for failure, 0 for succes.
int bs_set_bit(Bitset *bitset, size_t index, int value);

// Swiches the bit at index "index".
// Returns -1 for failure, 0 for succes.
int bs_switch_bit(Bitset *bitset, size_t index);

// Returns the bit ar index "index" (either 0 or 1).
// Returns -1 for failure.
int bs_get_bit(Bitset *bitset, size_t index);

// Stores in b1 the result of b1 OR b2.
// Returns -1 for failure, 0 for succes.
int bs_or(Bitset *b1, Bitset *b2);

// Stores in b1 the result of b1 AND b2.
// Returns -1 for failure, 0 for succes.
int bs_and(Bitset *b1, Bitset *b2);

// Stores in b1 the result of b1 XOR b2.
// Returns -1 for failure, 0 for succes.
int bs_xor(Bitset *b1, Bitset *b2);

// Negates the bitset given as parameter.
int bs_not(Bitset *bitset);

#endif // _LIBDSC_BITSET_H