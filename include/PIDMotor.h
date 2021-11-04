/** @file PIDMotor.h
 * @brief Motor data structure used to PID.
 *
 * Motor struct that contains all necessary variables and functions in order to PID. 
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "main.h"
#include "PIDProfile.hpp"

class PIDSystem;


/**
 * Motor struct that contains data members, getters, and setters used to use a
 * PID system on a motor.
*/
struct PIDMotor {
	/**
	 * Automatically enroll this motor into PIDSystem. If a PIDMotor with the
	 * same port is already enrolled, this instance will not work at all, even
	 * if the port becomes free later.
	 *
	 * @param port Integer that represents the port that this motor references.
	*/ 
	PIDMotor(unsigned int port);

	/**
	 * Automatically remove this motor from PIDSystem.
	*/ 
	~PIDMotor();

	/**
	 * Sets a target encoder value to PID towards.
	 *
	 * @param target Target encoder value.
	*/ 
	void Set(int target);

	/**
	 * Set the PIDProfile that this motor will use.
	 *
	 * @param PIDProfile Constant copy of a PIDProfile.
	*/ 
	void SetPID(PIDProfile pidProfile);

	/**
	 * @returns The port that this motor is referring to.
	*/ 
	unsigned int GetPort() const;

	/**
	 * @returns The target encoder value for this motor.
	*/ 
	int GetTarget() const;

	/**
	 * @returns A copy of the PIDProfile currently in use.
	*/ 
	const PIDProfile GetPID() const;

	/**
	 * @returns Whether or not the motor has reached its target (with +- `error`)
	*/
	bool AtTarget(unsigned int error) const;

	/**
	 * Internal function called by PIDSystem; Updates p, i, and d once.
	*/ 
	void _UpdatePID();

private:
	PIDProfile pidProfile;
	unsigned int port;
	int target;
	float proportion;
	float integral;
	float derivative;
	float pastError;
	bool targetSet;
};


#endif
