
#ifndef MOTOR_H
#define MOTOR_H

#include <API.h>

typedef unsigned char tMotor;
typedef char byte;

/*
  Reverses a motor port; This information is kept in an internal bitmask.
*/
void motor_set_sign(tMotor port, bool reversed);

/*
  Returns -1 if a port is reversed, 1 otherwise.
*/
byte motor_get_sign(tMotor port);

/*
  Sets the speed of a motor port taking into consideration whether it's
  reversed or not.
*/
void motor_set(tMotor port, byte speed);

/*
  Gets the speed of the motor. The speed returned takes into account whether
  it's reversed or not.
*/
byte motor_get(tMotor port);

/*
  Caps a value to the range accepted by motors [-127, 127].
*/
byte motor_cap(int value);

#endif
