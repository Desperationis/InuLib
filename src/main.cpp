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
 * Automatically retract claw until it hits a limit switch. Once it does, open
 * up the claw.
*/ 
void clawTurn(void* param) {
	SlewMotor arm(1);
	pros::ADIMotor claw(1);
	pros::ADIDigitalIn sensor(2);
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	while(true) {
		arm.Set(70);
		ControllerStream::Print(pros::E_CONTROLLER_MASTER, "Lifting arm; Wait");

		if(sensor.get_value() != 0) {
			arm.Set(0);
			pros::delay(400);
			claw.set_value(80);
			pros::delay(900);
			ControllerStream::Print(pros::E_CONTROLLER_MASTER, "");
			claw.set_value(0);
			break;
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) 
			break;

		pros::delay(5);
	}
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
	callback.SyncCallback(pros::E_CONTROLLER_DIGITAL_A, clawTurn);
	pros::ADIMotor claw(1);

	while(true) {
		callback.PollController();

		// Current workaround for using controller callbacks since only once
		// instance of SlewMotor may exist for a given port; Simply declare the
		// instances after checking the controller.
		SlewMotor topleft(20);
		SlewMotor topright(19);
		SlewMotor bottomright(18);
		SlewMotor bottomleft(17);
		SlewMotor basket(11);
		SlewMotor arm(1);

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
		basket.Set(0);
		arm.Set(0);
		claw.set_value(0);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			basket.Set(40);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			basket.Set(-40);
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			arm.Set(40);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			arm.Set(-40);
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			claw.set_value(-80);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			claw.set_value(80);
		}

		pros::delay(20);
	}
}
