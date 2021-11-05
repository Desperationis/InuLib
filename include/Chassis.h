/** @file Chassis.h
 * @brief Class for moving a chassis.
 *
 * Abstract class used to move a chassis.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include "main.h"
#include "PIDMotor.h"
#include <cstdint>

/**
 * Abstract class used for all chassis.
*/
class Chassis {
public:
	Chassis() { 
		errorLevel = 10;
	};

	virtual void TurnA(double degrees) = 0;

	virtual void Turn(double ticks) = 0;

	virtual void Forward(double ticks) = 0;

	virtual void Backward(double ticks) = 0;

	virtual bool IsSettled() = 0;

	virtual void SetError(unsigned int error) {
		this->errorLevel = error;
	};

	virtual void MaxVelocity(std::int32_t velocity) {
		maxVelocity = velocity;
	}

protected:
	unsigned int errorLevel;
	std::int32_t maxVelocity;
};


#endif
