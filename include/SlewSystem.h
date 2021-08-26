/** @file SlewSystem.h
 * @brief System for slewing motors.
 *
 * Description
 */

#ifndef SLEWSYSTEM_H
#define SLEWSYSTEM_H

#include "main.h"
#include <map>

class SlewMotor;

/**
 * Static class that runs the slew task in the background.
*/ 
class SlewSystem {
public:
	static void Start();

	static void SetDelay(unsigned int delay);

	static void EnrollMotor(SlewMotor* motor);

	static void RemoveMotor(SlewMotor* motor);

	static bool IsRunning();

	static void Stop();

private:
	static void SlewTask(void* parameters);

	// Interpolates between two values by a maximum amount
	static unsigned int Interpolate(unsigned int start, unsigned int end, 
					unsigned int maximum);

private:
	static pros::Task* slewTask;
	static std::map<unsigned int, SlewMotor*> motorMap;

	static unsigned int delay;
	static bool running;
};


#endif
