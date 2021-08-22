#include "BitManip.h"

void bit_set(int16_t* mask, ubyte position) {
    *mask |= (1 << position);
}

void bit_clear(int16_t* mask, ubyte position) {
    *mask &= ~(1 << position);
}

bool bit_read(int16_t* mask, ubyte position) {
    return (*mask >> position) % 2 == 1;
}
