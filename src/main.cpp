#include "main.h"
#include "inu/InuException.hpp"
#include "inu/terminal/Color.h"
#include "inu/util/PIDProfile.hpp"
#include "inu/wrapper/LineSensor.h"
#include "inu/wrapper/Motor.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/wrapper/InertialSensor.h"
#include "inu/background/CameraRainbowFlex.h"
#include "inu/controller/ControllerStream.h"
#include "inu/motor/engines/VelocityEngine.h"
#include "inu/motor/engines/VoltageEngine.h"
#include "inu/motor/engines/EncoderEngine.h"
#include "inu/motor/engines/SlewEngine.h"
#include "inu/motor/MechMotor.hpp"
#include "inu/nav/FieldController.h"
#include "inu/chassis/XChassis.h"
#include "inu/chassis/TankChassis.h"
#include "inu/nav/assignment/DiskAssignment.h"
#include "inu/util/VectorMath.hpp"
#include "inu/util/FieldPoint.h"
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

//#define LOGO

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
	pros::delay(1000);
	pros::delay(2000);
}


void opcontrol() {
	pros::ADIDigitalOut piston('A');
	pros::ADIDigitalOut cuc('B');
	cuc.set_value(0);


	auto pchassis = std::make_shared<XChassis>(1, 19, 5, 7);
	inu::GPS gps(8);
	gps.SetHeadingOffset(-90);
	//gps.SetOffset(-0.055, 0.076);


	FieldController fieldController(pchassis, gps);
	/*fieldController.LinearTo(0.9, -1.11);
	fieldController.TurnTo(180);
	fieldController.LinearTo(1.086, -1.48);
	pros::delay(5000);

	fieldController.LinearTo(-1.2, 0.97);
	fieldController.TurnTo(270);
	fieldController.LinearTo(-1.53, 0.97);
	pros::delay(5000);
	fieldController.LinearTo(0.5, -1.2);*/


	//pchassis->Stop();
	inu::MechMotor shooter(3);
	shooter.ChangeEngine<engine::SlewEngine>();
	auto slew = shooter.GetEngine<engine::SlewEngine>().lock();
	slew->SetSlewRate(5);

	inu::MechMotor intake(20);
	intake.ChangeEngine<engine::SlewEngine>();
	auto slew2 = intake.GetEngine<engine::SlewEngine>().lock();
	slew2->SetSlewRate(15);


	inu::Motor stick(2);
	inu::Motor rollers(11);
	bool shooterOn = false;

	Stopwatch w;
	bool pressed = false;

	bool vectorDrive = false;
	w.Mark();
	while(true) {
		pros::delay(20);
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		intake.SetTarget(0);
		stick.Move(0);
		rollers.Move(0);

		piston.set_value(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT));
		cuc.set_value(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT));

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			if(shooterOn)
				shooter.SetTarget(0);
			else
				shooter.SetTarget(80);

			shooterOn = !shooterOn;
		}


		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) 
			intake.SetTarget(127);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) 
			intake.SetTarget(-127);

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) 
			vectorDrive = !vectorDrive;

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) 
			stick.Move(127);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) 
			stick.Move(-127);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) 
			rollers.Move(127);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) 
			rollers.Move(-127);

		shooter.Execute();
		intake.Execute();

		if(!vectorDrive) {
			pchassis->RawSwerve(y, x, turn);
		}
		else {
			Vector<MathPoint> dir = Vector<FieldPoint>(x, y).ConvertTo<MathPoint>();
			Vector<MathPoint> robotVector = VectorMath::FromDegrees(-gps.GetHeading(), 1);

			pchassis->VectorPush(dir.Magnitude(), turn, robotVector, dir);
		}

		if(w.GetElapsed() > 1000) {
			auto info = gps.GetInfo();

			std::cout<<"GPS X: " << info.x << std::endl;
			std::cout<<"GPS Y: " << info.y << std::endl;
			w.Mark();
		}

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
			fieldController.LookAt(1.35, 1.3);


	}



	//////////////////////////////////////// TEST HOW MANY DISKS IT CAN DETECT
	inu::VisionSensor vision(13);
	auto sig = pros::Vision::signature_from_utility(1, 1087, 1919, 1502, -4855, -3903, -4378, 2.900, 0);
	vision.SetSignature(0, &sig);
	vision.SetMinimumArea(20);
	vision.SetCenterPoint(90,50);

	auto disk = DiskAssignment(vision);


	while(true) {
		disk.Run();

		pros::delay(500);
	}


	//////////////////////////////////////// CONTROL WITH VECTOR PUSH
	/*XChassis chassis(11, 5, 20, 6);


	inu::InertialSensor imu(15);
	Vector robotVector = Vector<FieldPoint>::FromDegrees(-imu.GetRotation(), 1);

	//chassis.VectorPush(40, 0, robotVector, Vector<FieldPoint>(1,1));
	pros::delay(1000);
	//chassis.VectorPush(40, 0, robotVector, Vector<FieldPoint>(-1,-1));
	pros::delay(500);
	//chassis.VectorPush(40, 0, robotVector, Vector<FieldPoint>(1,-1));
	pros::delay(1000);
	chassis.Stop();

	inu::Stopwatch watch;
	watch.Mark();

	while(true) {
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		//chassis.RawSwerve(y, x, turn);
		inu::InertialSensor imu(15);

		// Must be negative as imu.GetRotation is positive the other way
		// Cast to radians as GetRotation is in degrees
		Vector robotVector = Vector<FieldPoint>::FromDegrees(-imu.GetRotation(), 1);
		Vector<FieldPoint> tmp(x,y);
		//chassis.VectorPush(tmp.Magnitude(), turn, robotVector, tmp);
		pros::delay(20);

		if(watch.GetElapsed() > 2000) {
			std::cout<<imu.GetRotation() << std::endl;
			watch.Mark();
		}
	}



	///////////////////////////////////// OLD COMPETITION CODE
	try {
		inu::ControllerStream stream;
		stream.Start();

		inu::Motor topleft(20);
		inu::Motor topright(12);
		inu::Motor bottomleft(10);
		inu::Motor bottomright(1);
		inu::Motor intake(11);
		inu::Motor rollers(19);

		inu::MechMotor shooter1(9);
		shooter1.ChangeEngine<engine::SlewEngine>();

		inu::MechMotor shooter2(13);
		shooter1.ChangeEngine<engine::SlewEngine>();

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
			shooter1.SetTarget(0);
			shooter2.SetTarget(0);
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
				shooter1.SetTarget(-127 * shooterMult);
				shooter2.SetTarget(127 * shooterMult);
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
	}*/


	// In case we exit; Delay indefinitely so that the motors don't get 
	// frozen with their velocity
	while(true)
		pros::delay(10);
}
