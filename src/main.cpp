#include "main.h"
#include "SlewMotor.h"
#include "SlewSystem.h"
#include "PIDMotor.h"
#include "PIDSystem.h"
#include "PIDProfile.hpp"
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
	SlewSystem::Start();
	SlewMotor topleft(20);
	SlewMotor topright(19);
	SlewMotor bottomright(18);
	SlewMotor bottomleft(17);
	SlewMotor basket(11);
	SlewMotor arm(1);
	pros::ADIMotor claw(1);

	while(true) {
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		topleft.Set(x + y + turn);
		topright.Set(x - y + turn);
		bottomleft.Set(-x + y + turn);
		bottomright.Set(-x - y + turn);

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
			arm.Set(80);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			arm.Set(-80);
		}

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			claw.set_value(80);
		}
	
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			claw.set_value(-80);
		}

		pros::delay(20);
	}
}
