/** @file ControllerStream.h
 * @brief System for printing out to a controller.
 *
 * System that controls streaming to a controller.
 */

#ifndef CONTROLLERSTREAM_H
#define CONTROLLERSTREAM_H

#include "main.h"
#include "pros/misc.h"
#include <map>

/**
 * Static class that runs the a background task to print to the controller.
 * Use Start() and End() to control the task.
*/ 
class ControllerStream {
public:
	/**
	 * Starts the background task in the background. This must be called before
	 * something is outputted to the controller.
	*/ 
	static void Start();

	/**
	 * Sets the task delay of the background task.
	 *
	 * @param delay That represents the amount of time, in milliseconds,
	 * the task will wait every iteration. The default is 60 milliseconds.
	 * If the delay is below 50 ms, nothing will happen
	*/ 
	static void SetDelay(unsigned int delay);

	/**
	 * Print out a message to the controller. If more than one message is
	 * printed out within a interval of `delay` (default is 60ms), only the
	 * most recent statement will be printed. 
	 *
	 * If the message is the exact same as the previous, nothing will happen.
	 * This is to prevent the controller from "blinking" and to increase
	 * performance.
	 *
	 * If nullptr is passed nothing will happen.
	*/ 
	static void Print(pros::controller_id_e_t controllerID, const char* content);

	/**
	 * @returns Whether or not the task is running.
	*/
	static bool IsRunning();

	/**
	 * Stops the background task; Printing will not do anything until Start()
	 * is called again.
	*/ 
	static void Stop();

private:
	static void PrintTask(void* parameters);

private:
	static pros::Task* printTask;
	static std::map<pros::controller_id_e_t, const char*> requestMap;
	static std::map<pros::controller_id_e_t, const char*> printedMap;

	static unsigned int delay;
	static bool running;
};


#endif
