#include "BitManip.h"

void bit_set(int16_t* mask, byte position) {
  *mask |= (1 << position);
}

void bit_clear(int16_t* mask, byte position) {
  *mask &= ~(1 << position);
}

bool bit_read(int16_t* mask, byte position) {
  return (*mask >> position) == 1;
}
