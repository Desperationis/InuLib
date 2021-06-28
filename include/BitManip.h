#ifndef BITMANIP_H
#define BITMANIP_H

#include "Motor.h"

/*
    Set a bit (1) to a specific position in a bitmask.
*/
void bit_set(int16_t* mask, byte position);

/*
    Clear a bit to 0 in a specific position in a bitmask.
*/
void bit_clear(int16_t* mask, byte position);

/*
    Return true if the bit of the mask at a position is 1, return false
    otherwise.
*/
bool bit_read(int16_t* mask, byte position);

#endif
