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
#include "pros/misc.h"
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

void DriverControl(std::shared_ptr<AutoXChassis> chassis, AutoXChassisBuilder& builder, std::shared_ptr<ArmAssembly> armAssembly) {
	inu::Motor arm(1);
	inu::ADIMotor elbow1('D');
	inu::ADIMotor elbow2('C');
	inu::Motor autoClaw(10);
	inu::Motor basket(18);
	autoClaw.SetBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

	bool deathMode = false;

	while(true) {
		pros::Controller controller(pros::E_CONTROLLER_MASTER);
		int x = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int y = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis->RawSwerve(y, x, turn);

		autoClaw.MoveVelocity(0);
		elbow1.Set(0);
		elbow2.Set(0);
		arm.Move(0);
		armAssembly->MoveArm(0);
		basket.Move(0);


		if(deathMode) {
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				arm.MoveVelocity(-50);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				arm.MoveVelocity(50);
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
		}
		if(!deathMode) {
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
				armAssembly->MoveArm(-20000);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
				armAssembly->MoveArm(20000);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				autoClaw.Move(80);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
				autoClaw.Move(-80);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
				Collect(armAssembly);
			}
			if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
				armAssembly->Release();
				armAssembly->LightlyGrab();
			}
		}


		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
			basket.Move(50);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
			basket.Move(-50);
		}


		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) && !deathMode) {
			deathMode = true;
			builder.SetMotors(6, 20, 5, 11);
			chassis->Rebuild(builder);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && deathMode) {
			deathMode = false;
			builder.SetMotors(11,5,20,6);
			chassis->Rebuild(builder);
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
		armBuilder.SetArmMotor(19, PIDProfile(1.0f));
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


		// Get first Jenga Brick
		armAssembly->MoveArm(2550);
		chassis->Forward(350);
		follower->FollowLine(1000, 40);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);
		armAssembly->Grab();
		armAssembly->Retract();
		armAssembly->Release();

		// Go to kittens
		follower->FollowLine(1450, 40);
		armAssembly->MoveArm(1950);
		chassis->TurnA(45);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);
		chassis->TurnA(-45 - 180);

		// Go back and turn left then right to face villain
		follower->FollowLine(600, 40);
		chassis->TurnA(-90);
		follower->FollowLine(60);
		armAssembly->MoveArm(600);
		chassis->TurnA(90);
		chassis->StrafeLeft(100);

		// Get the first block
		while(!armAssembly->AtTarget(10))
			pros::delay(10); 
		follower->FollowLine(350, 40);
		armAssembly->Grab();
		armAssembly->Retract();
		armAssembly->Release();

		// Get the cup for villain
		armAssembly->MoveArm(2350);
		follower->FollowLine(1100, 40);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);
		armAssembly->LightlyGrab();
		armAssembly->MoveArm(-1000);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);

		// Stack it on villain
		chassis->Backward(100);
		chassis->TurnA(-15);
		armAssembly->MoveArm(800);
		while(!armAssembly->AtTarget(10))
			pros::delay(10);
		armAssembly->Release();
		armAssembly->Retract();

		// Turn back and go to central block.
		chassis->TurnA(-180 + 15);
		follower->FollowLine(850, 60);
		chassis->StrafeLeft(600);

		// Crank up turning speed 
		chassisOptions.maxVelocity = 100;
		builder.SetChassisOptions(chassisOptions);
		gyroOptions.gyroPID.p = 1.2;
		builder.SetGyro(15, gyroOptions);
		chassis->Rebuild(builder);

		// Turn back, do 360 turn, then go to final exit block
		chassis->TurnA(360 + 20);
		chassis->Forward(2000);

		DriverControl(chassis, builder, armAssembly); // Control chassis
		CalibrateThreshold(follower);
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
