/** @file PIDSystem.h
 * @brief Custom PID system for accurate movement.
 *
 * Custom PID system for accurate movement on a motor-by-motor basis.
 */
#ifndef PIDSYSTEM_H
#define PIDSYSTEM_H

#include "main.h"
#include <map>

struct PIDMotor;

/**
 * Static class that runs the PID task in the background. Use Start() to start
 * the PID task and Stop() to end it.
*/ 
class PIDSystem {
public:
	/**
	 * Starts the PID task in the background. Note that if you don't call this
	 * function before using PIDMotor instances, nothing will happen to those
	 * motors until this is called.
	*/ 
	static void Start();

	/**
	 * Sets the task delay of the PID task.
	 *
	 * @param delay That represents the amount of time, in milliseconds, the PID task
	 * will wait every iteration. The default is 10 seconds for accuracy. Lowering this 
	 * value will increase accuracy at the cost of increased computation, and vise versa.
	*/ 
	static void SetDelay(unsigned int delay);

	/**
	 * Adds a PIDMotor to be controlled by the background PID process; This
	 * happens automatically whenevery a new PIDMotor instance is created. If
	 * the port is already occupied by another PIDMotor, nothing will happen
	 * and the first PIDMotor to be enrolled will not be removed.
	 *
	 * It is important to note that once this is done it is absolutely not
	 * recommended to control this port at all in any other process to avoid
	 * conflict. Remove the PIDMotor with RemoveMotor() or use its destructor.
	 *
	 * @param motor Pointer to the motor you want to enroll.
	*/ 
	static void EnrollMotor(PIDMotor* motor);

	/**
	 * Removes a PIDMotor from the background slew process. This is
	 * automatically called by PIDMotor in its destructor. If at any moment
	 * you don't want a motor to be controlled by the slew task, remove it with
	 * this function. `motor` doesn't have to be the actual instance of the
	 * PIDMotor since this only looks at its port.
	 *
	 * @param motor Pointer to the motor you want to remove; If you lost
	 * it the original instance, simply create a new PIDMotor with the same
	 * port.
	*/ 
	static void RemoveMotor(PIDMotor* motor);

	/**
	 * @returns Whether or not the slew task is running.
	*/
	static bool IsRunning();

	/**
	 * Stops the PID task. If you call this, all PIDMotors will be removed.
	*/ 
	static void Stop();
private:
	static void PIDTask(void* parameters);

private:
	static pros::Task* PIDtask;
	static std::map<unsigned int, PIDMotor*> motorMap;

	static unsigned int delay;
	static bool running;
};


#endif
