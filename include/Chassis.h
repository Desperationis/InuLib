/** @file Chassis.h
 * @brief Class for moving a chassis.
 *
 * Abstract class used to move a chassis.
*/


// NOTE: Due to time, this will be a concrete class used for X-drive

#ifndef CHASSIS_H
#define CHASSIS_H

#include "main.h"
#include "PIDMotor.h"

class Chassis {
public:
	Chassis(int topleft, int topright, int bottomleft, int bottomright);

	void turnA(double degrees);

	void turn(double ticks);

	void forward(double ticks);

private: 
	PIDMotor topleftMotor, toprightMotor;
	PIDMotor bottomleftMotor, bottomrightMotor;
};


#endif
