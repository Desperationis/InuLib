#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/wrapper/ADIMotor.h"
#include "inu/wrapper/Motor.h"
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <memory>
#include <algorithm>
#include <stdexcept>


using namespace inu;

#define LOGO

/**
 * Runs initialization code. This occurs as soon as the program is started.
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

#ifdef LOGO
#include "inu/Logo.hpp"
void initialize() {
	//pros::lcd::initialize();
	inu::Logo::Draw();
#endif
#ifndef LOGO
	void initialize() {
		pros::lcd::initialize();
#endif	

	// This delay is REQUIRED for the program to work; Without this, core
	// components may or may not be initialized (i.e. inertial sensor) and 
	// return wicked weird values like NaN
	pros::delay(3000);
}

void opcontrol() {
		inu::Motor topleft(6);
		inu::Motor topright(20);
		inu::Motor bottomleft(5);
		inu::Motor bottomright(11);
		inu::ADIMotor arm1('A');
		inu::ADIMotor arm2('B');
		inu::ADIMotor elbow('C');

		while(true) {
			pros::Controller controller(pros::E_CONTROLLER_MASTER);
			int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
			int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

			topleft.Move(std::clamp<int>(x + y + turn, -100, 100));
			topright.Move(std::clamp<int>(x - y + turn, -100, 100));
			bottomleft.Move(std::clamp<int>(-x + y + turn, -100, 100));
			bottomright.Move(std::clamp<int>(-x - y + turn, -100, 100));

			elbow.Set(0);

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				arm1.Set(-127);
				arm2.Set(-127);
			}
			else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				arm1.Set(127);
				arm2.Set(127);
			}
			else {
				arm1.Set(0);
				arm2.Set(0);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				elbow.Set(127);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				elbow.Set(-127);
			}

			pros::delay(10);
		}


	// In case we exit; Delay indefinitely so that the motors don't get 
	// frozen with their velocity
	while(true)
		pros::delay(10);
}
