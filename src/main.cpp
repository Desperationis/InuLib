#include "main.h"
#include "inu/InuException.hpp"
#include "inu/terminal/Color.hpp"
#include "inu/motor/background/PIDVisionMotor.h"
#include "inu/motor/background/SlewMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoXChassisBuilder.h"
#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/wrapper/LineSensor.h"
#include "inu/wrapper/Motor.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/wrapper/InertialSensor.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/auto/ArmAssemblyBuilder.h"
#include "inu/auto/ColorFollower.h"
#include "inu/auto/ColorFollowerBuilder.h"
#include "inu/background/CameraRainbowFlex.h"
#include "inu/controller/ControllerStream.h"
#include "inu/motor/engines/VelocityEngine.h"
#include "inu/motor/engines/VoltageEngine.h"
#include "inu/motor/engines/AbsoluteEngine.h"
#include "inu/motor/engines/RelativeEngine.h"
#include "inu/motor/engines/SlewEngine.h"
#include "inu/motor/MechMotor.hpp"
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
	MechMotor motor(20);
	MechMotor motor2(20);
	motor.ChangeEngine<engine::SlewEngine>();
	auto ea = motor.GetEngine<engine::SlewEngine>();

	std::cout << Color::FG_GREEN << "# of references of weak: " << ea.use_count() << std::endl;
	
	{
		auto e = ea.lock();
		e->SetSlewRate(5);

		for(int i = 0; i < 3; i++) {
			e->SetTarget(10 * (i % 2 == 0 ? -1 : 1));
			e->Execute();
			std::cout << Color::FG_BLUE << "Setting motor speed to " << 100 * (i % 2 == 0 ? -1 : 1) << Color::FG_DEFAULT << std::endl;
			pros::delay(2000);
		}

		e->Shutdown();
		pros::delay(200);
	

		motor2.ChangeEngine<engine::SlewEngine>();
		auto ea2 = motor2.GetEngine<engine::SlewEngine>();
		auto e2 = ea2.lock();
		e2->SetTarget(-10);
		e2->Execute();
		
	}




	std::cout << Color::FG_GREEN << "# of references of weak: " << ea.use_count() << std::endl;

	while(true)
		pros::delay(50);

	try {
		inu::ControllerStream stream;
		stream.Start();

		inu::Motor topleft(20);
		inu::Motor topright(12);
		inu::Motor bottomleft(10);
		inu::Motor bottomright(1);
		inu::Motor intake(11);
		inu::Motor rollers(19);

		inu::SlewMotor shooter1(9);
		inu::SlewMotor shooter2(13);

		bool reverseForward = false;
		bool shooterToggle = false;

		bool pressed1 = false;
		bool pressed2 = false;
		bool pressed3 = false;
		bool pressed4 = false;
		float shooterMult = 0.5;

		while(true) {
			pros::Controller controller(pros::E_CONTROLLER_MASTER);
			int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

			if(!reverseForward) {
				topleft.Move(std::clamp<int>(y + turn, -100, 100));
				topright.Move(std::clamp<int>(-y + turn, -100, 100));
				bottomleft.Move(std::clamp<int>(y + turn, -100, 100));
				bottomright.Move(std::clamp<int>(-y + turn, -100, 100));
			}
			else {
				topleft.Move(std::clamp<int>(-y + turn, -100, 100));
				topright.Move(std::clamp<int>(y + turn, -100, 100));
				bottomleft.Move(std::clamp<int>(-y + turn, -100, 100));
				bottomright.Move(std::clamp<int>(y + turn, -100, 100));
			}

			intake.MoveVelocity(0);
			shooter1.Set(0);
			shooter2.Set(0);
			rollers.Move(0);

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				intake.Move(127);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				intake.Move(-127);
			}

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
				rollers.Move(127);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
				rollers.Move(-127);
			}

			// Shooter Speed Code
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && !pressed1) {
				controller.rumble("-");
				shooterMult = std::clamp<float>(shooterMult + 0.1f, 0.3f, 1.0f);
			}
			pressed1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) && !pressed2) {
				controller.rumble("-");
				shooterMult = std::clamp<float>(shooterMult - 0.1f, 0.3f, 1.0f);
			}
			pressed2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);


			// Reverse Code
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && !pressed3) {
				reverseForward = !reverseForward;
			}
			pressed3 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

			// Shooter code
			if(shooterToggle) {
				shooter1.Set(-127 * shooterMult);
				shooter2.Set(127 * shooterMult);
			}

			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && !pressed4) {
				shooterToggle = !shooterToggle;
			}
			pressed4 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

			pros::delay(10);
		}
	}
	catch(InuException e) {
		std::cout << Color::FG_RED << e.what() << Color::FG_DEFAULT << std::endl;
		throw std::runtime_error("InuException thrown");
	}


	// In case we exit; Delay indefinitely so that the motors don't get 
	// frozen with their velocity
	while(true)
		pros::delay(10);
}
