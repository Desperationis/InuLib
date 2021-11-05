#include "main.h"
#include "PIDMotor.h"
#include "PIDProfile.hpp"
#include "Chassis.h"
#include "XChassis.h"
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
	Chassis* chassis = new XChassis(1,2,3,4);
	chassis->turn(2500);
	pros::delay(4000);
	chassis->turn(-2500);

	while(true) {
		pros::delay(10000);
	}
}
