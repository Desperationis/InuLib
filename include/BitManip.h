/** @file BitManip.h
 * @brief Provides bit-manipulation functions.
 *
 * Provides bit-manipulation functions. This is usually used to make a bitmask
 * in lieu of an array.
 */

#ifndef BITMANIP_H
#define BITMANIP_H

#include "main.h"
#include "Motor.h"

/**
 * Set a bit to a specific position in a bitmask.
 *
 * @param mask Pointer to bitmask to manipulate.
 * @param position Positive integer representing the amount of shift this bit
 * will be set to.
*/
void bit_set(int16_t* mask, ubyte position);

/**
 * Clear a bit to 0 in a specific position in a bitmask.
 *
 * @param mask Pointer to bitmask to manipulate.
 * @param position Positive integer representing the amount of shift the bit
 * you want cleared is.
*/
void bit_clear(int16_t* mask, ubyte position);

/*
 * Read the bit at a specific position in a bitmask.
 *
 * @param mask Pointer to bitmask to manipulate.
 * @param position Positive integer representing the amount of shift the bit
 * you want read is.
 * @return True if the bit of the mask at a position is on.
*/
bool bit_read(int16_t* mask, ubyte position);

#endif
