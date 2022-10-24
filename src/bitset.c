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

int bs_or(Bitset *b1, Bitset *b2)
{
    // Check if the bitsets are alloc'ed.
    if (_bs_is_allocated(b1) == -1 || _bs_is_allocated(b2) == -1)
        return -1;

    // Return failure if the bitsets are of different lengths.
    if (b1->size != b2->size)
        return -1;

    // OR them together.
    for (int i = 0; i < b1->size; i++)
        bs_set_bit(b1, i, bs_get_bit(b1, i) | bs_get_bit(b2, i));
    return 0;
}

int bs_and(Bitset *b1, Bitset *b2)
{
    // Check if the bitsets are alloc'ed.
    if (_bs_is_allocated(b1) == -1 || _bs_is_allocated(b2) == -1)
        return -1;

    // Return failure if the bitsets are of different lengths.
    if (b1->size != b2->size)
        return -1;

    // AND them together.
    for (int i = 0; i < b1->size; i++)
        bs_set_bit(b1, i, bs_get_bit(b1, i) & bs_get_bit(b2, i));
    return 0;
}

int bs_xor(Bitset *b1, Bitset *b2)
{
    // Check if the bitsets are alloc'ed.
    if (_bs_is_allocated(b1) == -1 || _bs_is_allocated(b2) == -1)
        return -1;

    // Return failure if the bitsets are of different lengths.
    if (b1->size != b2->size)
        return -1;

    // XOR them together.
    for (int i = 0; i < b1->size; i++)
        bs_set_bit(b1, i, bs_get_bit(b1, i) ^ bs_get_bit(b2, i));
    return 0;
}


int bs_not(Bitset *bitset)
{
    // Check if the bitset is alloc'ed.
    if (_bs_is_allocated(bitset) == -1)
        return -1;

    // Negate the bitset.
    for (int i = 0; i < bitset->size; i++)
        bs_switch_bit(bitset, i);
    return 0;
}
