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

	// This delay is REQUIRED for the program to work; Without this, core
	// components may or may not be initialized (i.e. inertial sensor) and 
	// return wicked weird values like NaN
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
	p.p = 0.9;
	p.i = 0.1;
	p.d = 0;

	AutoXChassisBuilder builder;
	builder.SetMaxVelocity(60); 
	builder.SetMotors(1,2,3,4);
	builder.SetGyro(19);
	builder.SetTimeout(10);
	builder.SetGyroPID(p);
	builder.SetMaxAngleError(10); 
	builder.SetStalling(true);
	builder.SetTimeoutAlignLimit(0.5); // Makes a HUGE difference

	AutoXChassis* chassis = builder.Build();
	chassis->TurnA(90);
	chassis->Forward(2000);
	chassis->TurnA(180);
	chassis->Forward(2000);
	chassis->TurnA(90);
}
