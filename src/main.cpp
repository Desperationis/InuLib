#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
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
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <memory>
#include <algorithm>
#include <stdexcept>


using namespace inu;

#define LOGsO

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

void CalibrateThreshold(std::shared_ptr<XLineFollower> follower) {
	while(true) {
		bool detected = follower->LineDetected();
		pros::lcd::print(0, "Line detected: %d", (int)detected);

		int value = follower->RecommendThreshold();
		pros::lcd::print(6, "Recommended midpoint: %d", (int) value);

		pros::delay(10);
	}
}

/**
 * Given that the claw was set to a position, check if it reached that position,
 * and if so, grab the object, retract the arm, and let go.
*/ 
void Collect(std::shared_ptr<ArmAssembly> armAssembly) {
	while(!armAssembly->AtTarget(10)) {
		pros::delay(20);
	}
	armAssembly->Grab();
	armAssembly->Retract();
	armAssembly->Release();
}

void DriverControl() {
	inu::Motor topleft(6);
	inu::Motor topright(20);
	inu::Motor bottomleft(5);
	inu::Motor bottomright(11);
	inu::ADIMotor arm('A');
	inu::ADIMotor elbow1('D');
	inu::ADIMotor elbow2('C');

	bool switchSidesPressed = false;

	while(true) {
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		topleft.Move(std::clamp<int>(x + y + turn, -100, 100));
		topright.Move(std::clamp<int>(x - y + turn, -100, 100));
		bottomleft.Move(std::clamp<int>(-x + y + turn, -100, 100));
		bottomright.Move(std::clamp<int>(-x - y + turn, -100, 100));

		elbow1.Set(0);
		elbow2.Set(0);
		arm.Set(0);

		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			arm.Set(-127);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			arm.Set(127);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			elbow1.Set(127);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			elbow1.Set(-127);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			elbow2.Set(-127);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			elbow2.Set(127);
		}

		pros::delay(10);
	}
}

void opcontrol() {
	try {
		AutoChassisBuilder::AutoChassisOptions chassisOptions;
		chassisOptions.maxVelocity = 50;
		chassisOptions.timeoutLimit = 10;
		chassisOptions.timeoutAlignLimit = 0.5;
		chassisOptions.stalls = true;
		//chassisOptions.steadyStateEncoderError = 10;
		chassisOptions.steadyStateEncoderError = 8;

		AutoChassisBuilder::AutoChassisGyroOptions gyroOptions;
		gyroOptions.gyroPID.p = 1;
		gyroOptions.gyroPID.i = 0.10;
		gyroOptions.gyroPID.d = 0;
		gyroOptions.gyroPID.integralWindupLimit = 30;
		gyroOptions.gyroPID.integralLevelingError = 0;
		gyroOptions.steadyStateAngleError = 2;

		ArmAssemblyBuilder armBuilder;
		armBuilder.SetArmMotor(19, PIDProfile(0.7f));
		armBuilder.SetClawMotor(10);
		armBuilder.SetButton('A');
		armBuilder.SetArmMaximumVelocity(70);
		std::shared_ptr<ArmAssembly> armAssembly = armBuilder.Build();

		AutoXChassisBuilder builder;
		builder.SetMotors(11,5,20,6);
		builder.SetGyro(15, gyroOptions);
		builder.SetChassisOptions(chassisOptions);

		std::shared_ptr<AutoXChassis> chassis = builder.Build();

		XLineFollowerBuilder followerBuilder;
		followerBuilder.SetSensors( { 'H', 'B', 'G', 'F', 'E'} );
		followerBuilder.SetSensorError( { -300, -400, 0, -150, -50 } );
		followerBuilder.SetChassis(std::weak_ptr(chassis));
		followerBuilder.ActivateOnDark(false);
		followerBuilder.SetLightThreshold(600);
		std::shared_ptr<XLineFollower> follower = followerBuilder.Build();

		armAssembly->Retract();
		armAssembly->LightlyGrab();
		chassis->Forward(750);
		follower->FollowLine(2000, 40);
		armAssembly->MoveArm(1900);
		chassis->TurnA(45);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);
		chassis->TurnA(-45 - 180);
		follower->FollowLine(500, 40);
		chassis->TurnA(-90);
		follower->FollowLine(60);
		chassis->TurnA(90);
		armAssembly->Retract();
		armAssembly->Release();
		armAssembly->MoveArm(2350);
		follower->FollowLine(1450, 40);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);

		armAssembly->LightlyGrab();
		armAssembly->MoveArm(-1000);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);

		chassis->Backward(100);
		chassis->TurnA(-15);
		armAssembly->MoveArm(800);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);

		armAssembly->Release();

		CalibrateThreshold(follower);
		// Go to headquarters


		/*
		//follower->FollowLine(45);
		follower->FollowLine(45);
		chassis->TurnA(-360);
		armAssembly->MoveArm(2550);
		chassis->TurnA(-130);

		// Collect the first block on the bottomleft of headquarters 
		chassis->Forward(100);
		Collect(armAssembly);

		// Follow line till you get to the double blocks
		armAssembly->MoveArm(2250);
		if(!follower->LineDetected())
			throw InuException("AHHH");
		follower->FollowLine(1600, 45);

		// Collect top block
		Collect(armAssembly);

		// Collect Second block
		armAssembly->MoveArm(2650);
		chassis->Forward(100);
		Collect(armAssembly);

		// Follow line to get to the brick in front of the cats
		if(!follower->LineDetected())
			throw InuException("NOOOO");
		armAssembly->MoveArm(2550);
		follower->FollowLine(1750, 40);

		// Collect the brick
		Collect(armAssembly);

		// Go all the way to the cats.
		if(!follower->LineDetected())
			throw InuException("UUUUUUUU");
		armAssembly->MoveArm(1650);
		follower->FollowLine(45);

		// Angle up arm, then turn around to get the cats.
		while(!armAssembly->AtTarget(10)) {
			pros::delay(20);
		}
		chassis->TurnA(-360);

		// Go to cup with claw open
		chassis->TurnA(135);
		armAssembly->MoveArm(850);
		follower->FollowLine(2750, 45);

		// Lift up cup
		armAssembly->LightlyGrab();
		armAssembly->MoveArm(-900);
		while(!armAssembly->AtTarget(10)) {
			pros::delay(20);
		}
		follower->FollowLine(370, 30);
		chassis->TurnA(-18);
		armAssembly->MoveArm(700);
		while(!armAssembly->AtTarget(10)) {
			pros::delay(20);
		}
		armAssembly->Release();

		// Go back in line, and follow it to the topleft corner.
		armAssembly->Retract();
		chassis->TurnA(18);
		follower->FollowLine(40);

		// Face the next row of bricks and grab the first one.
		armAssembly->MoveArm(2550);
		chassis->TurnA(135);
		Collect(armAssembly);

		// Go all the back to the brick back at day job
		follower->FollowLine(3450, 50);
		armAssembly->MoveArm(2550);
		Collect(armAssembly);

		// Go back to headquarters
		follower->FollowLine(45);
		chassis->TurnA(-135);
		follower->FollowLine(45);*/
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
