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
	pros::delay(3000);
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
	PIDProfile p;
	p.p = 0.8;
	p.i = 0.05;
	p.d = 0;

	AutoXChassisBuilder builder;
	builder.SetMaxVelocity(40);
	builder.SetMotors(1,2,3,4);
	builder.SetGyro(19);
	builder.SetTimeout(10);
	builder.SetGyroPID(p);
	builder.SetMaxAngleError(5);

	AutoXChassis* chassis = builder.Build();
	chassis->TurnA(360);
}
