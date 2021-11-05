/** @file XChassis.h
 * @brief Class for moving a x-drive powered chassis.
 *
 * Chassis used to control a x-drive.
*/


// NOTE: Due to time, this will be a concrete class used for X-drive

#ifndef XCHASSIS_H
#define XCHASSIS_H

#include "main.h"
#include "PIDMotor.h"
#include "Chassis.h"


/**
 * Controls a x-drive powered chassis with a topleft, topright, bottomleft, and
 * bottomright motor.
*/ 
class XChassis : public Chassis {
public:
	/**
	 * topleft, topright, bottomleft, and bottomright are the motor ports of
	 * their respective motors. It is assumed that the motors are mounted such
	 * that, when powered with a positive speed, the entire chassis turns
	 * clockwise.
	*/ 
	XChassis(int topleft, int topright, int bottomleft, int bottomright);

	virtual void turnA(double degrees);

	virtual void turn(double ticks);

	virtual void forward(double ticks);

	virtual void backward(double ticks);

	virtual void strafeLeft(double ticks);

	virtual void strafeRight(double ticks);

	virtual bool isSettled();

private:
	PIDMotor* topleftMotor;
	PIDMotor* toprightMotor;
	PIDMotor* bottomleftMotor;
	PIDMotor* bottomrightMotor;
};


#endif
