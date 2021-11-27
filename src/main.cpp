#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
#include "inu/motor/background/PIDVisionMotor.h"
#include "inu/motor/background//SlewMotor.h"
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
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/vision.h"
#include <memory>
#include <algorithm>
#include <stdexcept>


using namespace inu;

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
		pros::lcd::print(1, "Recommended midpoint: %d", (int) value);
		pros::delay(10);
	}
}

void opcontrol() {
	try {

		/*pros::Motor test(20);
		test.set_reversed(true);
		test.move_relative(4000, 30);
		std::cout<<"moving"<<std::endl;

		pros::Vision vision(12);
		pros::Vision vision2(9);

		////////////////////////////// TESTING AREA //////////////////////////////

		std::vector<int> colors {
			RGB2COLOR(100, 0, 0), // RED
			RGB2COLOR(10, 255, 0), // ORANGE
			RGB2COLOR(0, 255, 0), // GREEN
			RGB2COLOR(0, 255, 10), // CYAN
			RGB2COLOR(0, 0, 100), // BLUE
			RGB2COLOR(1, 1, 100), // Purple
			//RGB2COLOR(100, 0, 100), // PINk
		};


		while(true) {
			std::cout<<test.get_position() << std::endl;

			for(auto color : colors) {
				vision.set_led(color);
				vision2.set_led(color);
				pros::delay(125);
			}

			pros::delay(200);
		}*/

		inu::ColorFollowerBuilder::ColorFollowerOptions colorOptions;
		colorOptions.exposure = 70;
		colorOptions.minimumArea = 200;
		colorOptions.sensitivity = 0.3f;
		colorOptions.zeroPoint = pros::E_VISION_ZERO_CENTER;

		pros::vision_signature sig = pros::Vision::signature_from_utility(2, 1013, 1725, 1370, 28047, 29127, 28586, 3.000, 0);

		AutoChassisBuilder::AutoChassisOptions chassisOptions;
		chassisOptions.maxVelocity = 60;
		chassisOptions.timeoutLimit = 10;
		chassisOptions.timeoutAlignLimit = 0.5;
		chassisOptions.stalls = true;
		chassisOptions.steadyStateEncoderError = 10;

		AutoChassisBuilder::AutoChassisGyroOptions gyroOptions;
		gyroOptions.gyroPID.p = 0.9;
		gyroOptions.gyroPID.i = 0.15;
		gyroOptions.gyroPID.d = 0;
		gyroOptions.gyroPID.integralWindupLimit = 50;
		gyroOptions.gyroPID.integralLevelingError = 0;

		AutoXChassisBuilder chassisBuilder;
		chassisBuilder.SetMotors(11,20,3,4);
		chassisBuilder.SetGyro(10, gyroOptions);
		chassisBuilder.SetChassisOptions(chassisOptions);

		std::shared_ptr<AutoXChassis> xchassis = chassisBuilder.Build();


		inu::ColorFollowerBuilder colorBuilder;
		colorBuilder.PushSensor(9, -50, 0);
		colorBuilder.PushSensor(12, 50, 0);
		colorBuilder.PushSignature(sig);
		colorBuilder.SetChassis(xchassis);
		colorBuilder.SetOptions(colorOptions);

		std::shared_ptr<ColorFollower> colorFollower = colorBuilder.Build();
		while(true) {
			colorFollower->Follow(3);
			/*std::cout<<"Objects on screen: ";
			std::cout<<pros::Vision(9).get_object_count();
			std::cout << " ";
			std::cout<<pros::Vision(12).get_object_count();
			std::cout<<std::endl;*/
			pros::delay(200);
		}

		ArmAssemblyBuilder armBuilder;
		armBuilder.SetArmMotor(18, PIDProfile(0.7f));
		armBuilder.SetClawMotor('A');
		armBuilder.SetButton('E');
		armBuilder.SetArmMaximumVelocity(100);
		std::shared_ptr<ArmAssembly> armAssembly = armBuilder.Build();

		/*while(true) {
			armAssembly->Retract();
			armAssembly->Release();
			armAssembly->MoveArm(2200);
			while(!armAssembly->AtTarget(30)) {
				pros::delay(20);
			}
			armAssembly->Grab();

			armAssembly->Retract();
			armAssembly->Release();
			armAssembly->MoveArm(2450);
			while(!armAssembly->AtTarget(30)) {
				pros::delay(20);
			}
			armAssembly->Grab();
		}*/


		// Need exceptions anything below	
		AutoXChassisBuilder builder;
		builder.SetMotors(11,20,3,4);
		builder.SetGyro(10, gyroOptions);
		builder.SetChassisOptions(chassisOptions);

		std::shared_ptr<AutoXChassis> chassis = builder.Build();

		XLineFollowerBuilder followerBuilder;
		followerBuilder.SetSensors( { 'B', 'F', 'G', 'H', 'C'} );
		followerBuilder.SetSensorError( { -500, -190, 0, 60, -400 } );
		followerBuilder.SetChassis(std::weak_ptr(chassis));
		followerBuilder.ActivateOnDark(false);
		followerBuilder.SetLightThreshold(350);
		
		std::shared_ptr<XLineFollower> follower = followerBuilder.Build();

		armAssembly->Retract();
		armAssembly->Release();
		follower->FollowLine(1000);
		armAssembly->MoveArm(2450);
		while(!armAssembly->AtTarget(30)) pros::delay(20);
		armAssembly->Grab();
		armAssembly->Retract();
		armAssembly->Release();
	}
	catch(InuException e) {
		std::cout << Color::FG_RED << e.what() << Color::FG_DEFAULT << std::endl;
		throw std::runtime_error("InuException thrown");
	}
}
