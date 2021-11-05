/** @file BackgroundMotorSystem.h
 * @brief System that updates motors' internal states
 *
 * System that updates all BackgroundMotors.
 */ 

#ifndef BACKGROUNDMOTORSYSTEM_H
#define BACKGROUNDMOTORSYSTEM_H

#include "main.h"
#include <array>
#include "BackgroundMotor.h"


class BackgroundMotorSystem {
public:
	static BackgroundMotorSystem* Instance();

	BackgroundMotorSystem();

	void SetDelay(unsigned int delay);

	void EnrollMotor(BackgroundMotor* motor);

	void RemoveMotor(BackgroundMotor* motor);

	void RemoveMotor(unsigned int port);

protected:

	void BackgroundTask(void* parameters);

protected:
	static BackgroundMotorSystem* instance; 
	pros::Task* backgroundTask;
	std::array<BackgroundMotor*, 20> motors;
	unsigned int delay;
};



#endif
