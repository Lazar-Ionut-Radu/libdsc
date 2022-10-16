#include "bitset.h"
#include <stdio.h>

Bitset *bs_create(size_t size)
{
    // Alloc memory for the Bitset. If malloc() failed return NULL.
    Bitset *bitset = malloc(sizeof(Bitset));
    if (bitset == NULL)
        return NULL;

    // Set the size.
    bitset->size = size;

    // Alloc memory for the array of bits.
    char size_bits; // The size of elements in the bits array.
    size_bits = size / 8;
    if (size % 8 != 0)
        size_bits++;
    
    // Also initialize it with 0s.
    bitset->bytes = calloc(size_bits, sizeof(char));
    if (bitset->bytes == NULL) {
        free(bitset);
        return NULL;
    }

    return bitset;
}

int _bs_is_allocated(Bitset *bitset)
{
    if (bitset == NULL)
        return -1;

    if (bitset->bytes == NULL)
        return -1;
    
    return 0;
}

void bs_free(Bitset *bitset)
{
    if (bitset == NULL)
        return;

    if (bitset->bytes)
        free(bitset->bytes);
    free(bitset);
    
    bitset = NULL;
}

int bs_set_bit(Bitset *bitset, size_t index, int value)
{
    // Return -1 if the bitset is not alloc'ed.
    if (_bs_is_allocated(bitset) != 0)
        return -1;

    // Return -1 if the index is invalid.
    if (index >= bitset->size)
        return -1;

    // Return -1 if the value is invalid (it should be 0 or 1).
    if (value != 0 && value != 1)
        return -1;

    // The byte in the "bits" array the bit changed belongs to.
    int byte = index / 8;
    // The bit in that byte the bit changed belongs to.
    int bit = index % 8;

    // Set the bit.
    if (value == 0) 
        bitset->bytes[byte] = bitset->bytes[byte] & (~bits[bit]);
    if (value == 1)
        bitset->bytes[byte] = bitset->bytes[byte] | bits[bit];

    return 0;
}

int bs_switch_bit(Bitset *bitset, size_t index)
{
    // Return -1 if the bitset is not alloc'ed.
    if (_bs_is_allocated(bitset) != 0)
        return -1;

    // Return -1 if the index is invalid.
    if (index >= bitset->size)
        return -1;

    // The byte in the "bits" array the bit changed belongs to.
    int byte = index / 8;
    // The bit in that byte the bit changed belongs to.
    int bit = index % 8;

    bitset->bytes[byte] = bitset->bytes[byte] ^ bits[bit];

    return 0;
}

int bs_get_bit(Bitset *bitset, size_t index)
{
    // Return -1 if the bitset is not alloc'ed.
    if (_bs_is_allocated(bitset) != 0)
        return -1;

    // Return -1 if the index is invalid.
    if (index >= bitset->size)
        return -1;

    // The byte in the "bits" array the bit changed belongs to.
    int byte = index / 8;
    // The bit in that byte the bit changed belongs to.
    int bit = index % 8;

    if ( (bitset->bytes[byte] & bits[bit]) != 0)
        return 1;
    return 0;
}

int main(void)
{
    Bitset *bitset = bs_create(17);
    bs_free(bitset);

    return 0;
}