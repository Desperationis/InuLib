#include "main.h"
#include "SlewMotor.h"
#include "SlewSystem.h"
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
	SlewSystem::Start();
	SlewMotor testMotor(2);

	SlewSystem::EnrollMotor(&testMotor);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	testMotor.SetRate(4);

	while (true) {
		int x = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);	
		testMotor.Set(x);
		pros::delay(20);
	}


	pros::Motor topleft_mtr(2);
	pros::Motor topright_mtr(9);
	pros::Motor bottomleft_mtr(1);
	pros::Motor bottomright_mtr(10);
	pros::Motor arm_mtr(8);
	pros::ADIMotor claw_mtr(8);

	while (true) {
		// X-Drive controller code
		int x = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		topleft_mtr.move(-y - x + turn);
		topright_mtr.move(y + x + turn);
		bottomleft_mtr.move(-y + x + turn);
		bottomright_mtr.move(y - x + turn);

		// Reset arm and claw motor every frame
		arm_mtr.move(0);
		claw_mtr.set_value(0);

		// Pair L1 and R1 to moving the arm up and down.
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			arm_mtr.move(50);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			arm_mtr.move(-50);
		}

		// Pair L2 and R2 to claw opening / closing
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			claw_mtr.set_value(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			claw_mtr.set_value(-127);
		}

		pros::delay(2);
	}
}
