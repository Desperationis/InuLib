#ifndef BITMANIP_H
#define BITMANIP_H

#include "Motor.h"

void bit_set(int16_t* mask, byte position);
void bit_clear(int16_t* mask, byte position);
bool bit_read(int16_t* mask, byte position);

#endif
