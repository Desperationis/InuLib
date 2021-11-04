#include "main.h"
#include "SlewMotor.h"
#include "SlewSystem.h"
#include "PIDMotor.h"
#include "PIDSystem.h"
#include "ControllerCallback.h"
#include "PIDProfile.hpp"
#include "ControllerStream.h"
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
	ControllerStream::Start();
	SlewSystem::Start();
	ControllerCallback callback(pros::E_CONTROLLER_MASTER);
	pros::ADIMotor claw(1);
	pros::Motor armOG(11); // Don't move arm with this; Only for absolute position

	// Do not ever use or run this statement because this is a very special
	// case where it interferes; PID has to be single-threaded
	// PIDSystem::Start();
	
	PIDMotor arm(11);
	PIDProfile profile;
	profile.p = 0.8;
	profile.i = 0;
	profile.d = 0;
	arm.SetPID(profile);

	while(true) {
		callback.PollController();

		// Current workaround for using controller callbacks since only once
		// instance of SlewMotor may exist for a given port; Simply declare the
		// instances after checking the controller.
		SlewMotor topleft(9);
		SlewMotor topright(10);
		SlewMotor bottomright(12);
		SlewMotor bottomleft(19);

		// X-Drive Controller Code
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		topleft.Set(x + y + turn);
		topright.Set(x - y + turn);
		bottomleft.Set(-x + y + turn);
		bottomright.Set(-x - y + turn);

		// Arm, claw, and basket code.
		claw.set_value(0);

		// Don't use arm.GetTarget() as it's set to 0 every iteration
		// of this loop; Dangerous
		double armTarget = armOG.get_position();

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			// Modify this at school; This changes the target of the PID arm 
			// By an amount that might be too slow for our gear ratio
			arm.Set(armTarget + 60);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			arm.Set(armTarget - 60);
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			claw.set_value(100);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			claw.set_value(-100);
		}

		arm._UpdatePID();

		pros::delay(20);
	}
}
