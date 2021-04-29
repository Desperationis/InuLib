#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <API.h>
#include "Motor.h"

/*
	Control chassis via an xdrive configuration where the corners are the wheels.
	Left joystick is for movement, right for turning. This assumes that, when all
	motors are powered with a positive value, the robot turns clockwise.
*/
void control_xdrivecorner();

/*
	Control chassis via an xdrive configuration where the edges are the wheels;
	The "front" of the robot is a wheel. Left joystick is for movement, right for
	turning. This assumes that, when all motors are powered with a positive value,
	the robot turns clockwise.
*/
void control_xdriveedge();

#endif
