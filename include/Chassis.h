/** @file Chassis.h
 * @brief Class for moving a chassis.
 *
 * Abstract class used to move a chassis.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include "main.h"
#include <cstdint>

/**
 * Abstract class used for all chassis.
*/
class Chassis {
protected:
	Chassis() = default;

public:
	virtual void TurnA(double degrees) = 0;

	virtual void Turn(double ticks) = 0;

	virtual void Forward(double ticks) = 0;

	virtual void Backward(double ticks) = 0;

	virtual bool IsSettled() = 0;

	virtual void MaxVelocity(std::int32_t velocity) {
		maxVelocity = velocity;
	}


protected:
	std::int32_t maxVelocity;
};


#endif
