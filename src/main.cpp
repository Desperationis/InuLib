#include "main.h"
#include "SlewMotor.h"
#include "SlewSystem.h"
#include "PIDMotor.h"
#include "PIDSystem.h"
#include "pros/misc.h"
#include "pros/motors.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
}

/**
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	PIDSystem::Start();
	PIDMotor topleft(9);
	PIDMotor topright(10);
	PIDMotor bottomleft(2);
	PIDMotor bottomright(9);


	float p = 0.4;
	float i = 0.001f;
	float d = 0.01f;

	topleft.SetP(p);
	topleft.SetI(i);
	topleft.SetD(d);

	topright.SetP(p);
	topright.SetI(i);
	topright.SetD(d);

	bottomleft.SetP(p);
	bottomleft.SetI(i);
	bottomleft.SetD(d);

	bottomright.SetP(p);
	bottomright.SetI(i);
	bottomright.SetD(d);

	//topleft.Set(100);
	topright.Set(-100);
	//bottomleft.Set(-100);
	//bottomright.Set(100);

	while(true) {
		pros::delay(20);
	}
}
