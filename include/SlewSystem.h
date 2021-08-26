/** @file SlewSystem.h
 * @brief System for slewing motors.
 *
 * System that slews motors SlewMotor in the background.
 */

#ifndef SLEWSYSTEM_H
#define SLEWSYSTEM_H

#include "main.h"
#include <map>

class SlewMotor;

/**
 * Static class that runs the slew task in the background. Use Start() to start
 * the slew task and Stop() to end it.
*/ 
class SlewSystem {
public:
	/**
	 * Starts the slew task in the background. Note that if you don't call this
	 * function before using SlewMotor instances, nothing will happen to those
	 * motors until this is called.
	*/ 
	static void Start();

	/**
	 * Sets the task delay of the slew task.
	 *
	 * @param delay That represents the amount of time, in milliseconds,
	 * the slew task will wait every iteration. The default is 20 milliseconds.
	 * Changing this value will effect slewing globally.
	*/ 
	static void SetDelay(unsigned int delay);

	/**
	 * Adds a SlewMotor to be controlled by the background slew process; This
	 * happens automatically whenever a new SlewMotor instance is created. If
	 * the port is already occupied by another SlewMotor, nothing will happen
	 * and the first SlewMotor to be enrolled will not be removed.
	 *
	 * It is important to note that once this is done it is absolutely not
	 * recommended to control this port at all in any other process to avoid
	 * conflict. Remove the SlewMotor with RemoveMotor() or use its destructor.
	 *
	 * @param motor Pointer to the motor you want to enroll.
	*/ 
	static void EnrollMotor(SlewMotor* motor);

	/**
	 * Removes a SlewMotor from the background slew process. This is
	 * automatically called by SlewMotor in its destructor. If at any moment
	 * you don't want a motor to be controlled by the slew task, remove it with
	 * this function. `motor` doesn't have to be the actual instance of the
	 * SlewMotor since this only looks at its port.
	 *
	 * @param motor Pointer to the motor you want to remove; If you lost
	 * it the original instance, simply create a new SlewMotor with the same
	 * port.
	*/ 
	static void RemoveMotor(SlewMotor* motor);

	/**
	 * @returns Whether or not the slew task is running.
	*/
	static bool IsRunning();

	/**
	 * Stops the slew task. If you call this, all SlewMotors will be removed.
	*/ 
	static void Stop();

private:
	static void SlewTask(void* parameters);

	/**
	 * Given two values, interpolate between them.
	 *
	 * @param start The starting value, positive or negative.
	 * @param end The target value, positive or negative.
	 * @param maximum The maximum difference between start and end that will be
	 * interpolated.
	 *
	 * @return The interpolated value.
	*/ 
	static unsigned int Interpolate(unsigned int start, unsigned int end, 
					unsigned int maximum);

private:
	static pros::Task* slewTask;
	static std::map<unsigned int, SlewMotor*> motorMap;

	static unsigned int delay;
	static bool running;
};


#endif
