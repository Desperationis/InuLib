/** @file SlewMotor.h
 * @brief Motor data structure used to slew.
 *
 * Motor struct that contains all necessary variables and functions in order to
 * slew.
 */

#ifndef SLEWMOTOR_H
#define SLEWMOTOR_H

#include "main.h"

class SlewSystem;

/**
 * Motor struct that contains data members, getters, and setters used to slew a
 * motor.
*/
struct SlewMotor {
public:
	/**
	 * Automatically enroll this motor into SlewSystem. If a SlewMotor with the
	 * same port is already enrolled, this instance will not work at all, even
	 * if the port becomes free later.
	 *
	 * @param port Integer that represents the port that this motor references.
	*/ 
	SlewMotor(unsigned int port);

	/**
	 * Automatically remove this motor from SlewSystem.
	*/ 
	~SlewMotor();

	/**
	 * Set the target speed of the motor to interpolate towards.
	 *
	 * @param speed Integer between -127 and 127. By default, this is set to 0.
	*/ 
	void Set(int speed);

	/**
	 * Set the rate at which the speed of the motor is interpolated towards the
	 * target speed; The maximum change in speed of the motor in a single
	 * update of SlewSystem.
	 *
	 * @param rate Positive integer of the max rate of change of motor speed.
	 */ 
	void SetRate(unsigned int rate);

	/**
	 * @return The port that this instance is referring to.
	*/ 
	unsigned int GetPort();

	/**
	 * @return The current maximum rate of change of motor speed this motor is
	 * configured for.
	*/ 
	unsigned int GetRate();

	/**
	 * @return The target speed of the motor.
	*/ 
	int GetTargetSpeed();

private:
	unsigned int port, rate;
	int targetSpeed;
};


#endif
