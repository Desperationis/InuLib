#include "main.h"
#include "inu/ControllerStream.h"
#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
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
	ControllerStream::Start();	
	PIDProfile p;
	p.p = 0.9;
	p.i = 0.15;
	p.d = 0;

	AutoXChassisBuilder builder;
	builder.SetMaxVelocity(60); 
	builder.SetMotors(11,20,3,4);
	builder.SetGyro(10);
	builder.SetTimeout(10);
	builder.SetGyroPID(p);
	builder.SetMaxAngleError(5); 
	builder.SetStalling(true);
	builder.SetTimeoutAlignLimit(0.5); // Makes a HUGE difference

	AutoXChassis* chassis = builder.Build();

	XLineFollowerBuilder followerBuilder;
	followerBuilder.SetSensors(6,7,8);
	followerBuilder.SetSensorError(250,0,0);
	followerBuilder.SetChassis(chassis);
	followerBuilder.ActivateOnDark(false);
	followerBuilder.SetLightThreshold(500); // Tune this

	XLineFollower* follower = followerBuilder.Build();
	while(true) {
		follower->FollowLine();
		pros::delay(20);
	}

	// Calibration code
	while(true) {
		bool detected = follower->LineDetected();
		pros::lcd::print(0, "Line detected: %d", (int)detected);

		int value = follower->RecommendThreshold();
		pros::lcd::print(1, "Recommended midpoint: %d", (int) value);
		pros::delay(10);
	}
}
