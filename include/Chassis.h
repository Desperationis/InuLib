/** @file Chassis.h
 * @brief Class for moving a chassis.
 *
 * Abstract class used to move a chassis.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include "main.h"
#include "PIDMotor.h"

/**
 * Abstract class used for all chassis.
*/
class Chassis {
public:
	Chassis() { 
		errorLevel = 10;
	};

	virtual void turnA(double degrees) = 0;

	virtual void turn(double ticks) = 0;

	virtual void forward(double ticks) = 0;

	virtual bool isSettled() = 0;

	virtual void setError(unsigned int error) {
		this->errorLevel = error;
	};

protected:
	unsigned int errorLevel;
};


#endif
