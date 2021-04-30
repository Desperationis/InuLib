#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <API.h>
#include "Motor.h"
#include "Slew.h"

/*
	Control chassis via an xdrive configuration where the corners are the wheels.
	Left joystick is for movement, right for turning. This assumes that, when all
	motors are powered with a positive value via the Motor module, the robot turns
  clockwise.
*/
void control_xdrivecorner();

/*
  Control chassis via an xdrive configuration where the corners are the wheels.
  Left joystick is for forward / backward, right for turning; Kind of like a
  racing game. This assumes that, when all motors are powered with a positive
  value via the Motor module, the robot turns clockwise.
*/
void control_xdrivecorner_gamer();


/*
	Control chassis via an xdrive configuration where the edges are the wheels;
	The "front" of the robot is a wheel. Left joystick is for movement, right for
	turning. This assumes that, when all motors are powered with a positive value
	 via the Motor module, the robot turns clockwise.
*/
void control_xdriveedge();


#endif
