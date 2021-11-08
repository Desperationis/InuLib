#include "main.h"
#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"

using namespace inu;

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
	AutoXChassisBuilder builder;
	builder.SetMaxVelocity(30);
	builder.SetMotors(1,2,3,4);
	builder.SetGyro(5);

	AutoXChassis* chassis = builder.Build();
	chassis->StrafeLeft(1000);
	pros::delay(4000);
	chassis->StrafeRight(1000);

	while(true) {
		pros::delay(10000);
	}
}
