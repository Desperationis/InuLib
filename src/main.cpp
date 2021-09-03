#include "main.h"
#include "SlewMotor.h"
#include "SlewSystem.h"
#include "PIDMotor.h"
#include "PIDSystem.h"
#include "pros/misc.h"

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
	PIDMotor topleft(2);
	PIDMotor topright(9);
	PIDMotor bottomleft(1);
	PIDMotor bottomright(10);

	float p = 1;
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

	topleft.Set(1000);
	topright.Set(-1000);
	bottomleft.Set(-1000);
	bottomright.Set(1000);

	while(true) {
		pros::delay(20);
	}

}
