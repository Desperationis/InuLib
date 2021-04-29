
#ifndef MOTOR_H
#define MOTOR_H

/*
  Reverses a motor port; This information is kept in an internal bitmask.
*/
void motor_set_sign(int port, bool reversed);

/*
  Returns -1 if a port is reversed, 1 otherwise.
*/
int motor_get_sign(int port);

/*
  Sets the speed of a motor port taking into consideration whether it's
  reversed or not.
*/
void motor_set(int port, int speed);

/*
  Gets the speed of the motor. The speed returned takes into account whether
  it's reversed or not.
*/
int motor_get(int port);

/*
  Caps a value to the range accepted by the motors [-127, 127].
*/
int motor_cap(int value);

#endif
