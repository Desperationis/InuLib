
#ifndef MOTOR_H
#define MOTOR_H

#include <API.h>


/*
  Reverses a motor port; This information is kept in an internal array.
*/
void setMotorSign(int port, bool reversed);

/*
  Sets the speed of a motor port taking into consideration whether it's
  reversed or not.
*/
void setMotor(int port, int speed);

/*
  Gets the speed of the motor. The speed returned takes into account whether
  it's reversed or not.
*/
int getMotor(int port);

/*
  Caps a value to the range accepted by the motors [-127, 127].
*/
int motorCap(int value);

#endif
