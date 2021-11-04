/*
 * Abstract class for moving the chassis via PID or gyro
 */ 

#ifndef CHASSIS_H
#define CHASSIS_H


#include "main.h"

class Chassis {
public:
	Chassis();

	void turnA(double degrees);

	void turn(double ticks);

	void forward(double ticks);
};


#endif
