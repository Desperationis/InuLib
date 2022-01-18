#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/PIDProfile.hpp"
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
		inu::Motor topleft(11);
		inu::Motor topright(20);
		inu::Motor bottomleft(3);
		inu::Motor bottomright(4);

		inu::PIDProfile armProfile;
		armProfile.p = 0.9;
		armProfile.i = 0.0;
		armProfile.d = 0.0;
		inu::PIDMotor arm(10, armProfile);

		while(true) {
			pros::Controller controller(pros::E_CONTROLLER_MASTER);
			int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
			int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

			topleft.Move(std::clamp<int>(x + y + turn, -70, 70));
			topright.Move(std::clamp<int>(x - y + turn, -70, 70));
			bottomleft.Move(std::clamp<int>(-x + y + turn, -70, 70));
			bottomright.Move(std::clamp<int>(-x - y + turn, -70, 70));

			arm.Set(arm.GetPosition());

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				arm.Set(arm.GetPosition() - 50);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				arm.Set(arm.GetPosition() + 50);
			}

			pros::delay(10);
		}


	// In case we exit; Delay indefinitely so that the motors don't get 
	// frozen with their velocity
	while(true)
		pros::delay(10);
}
