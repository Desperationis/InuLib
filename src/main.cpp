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
#include "inu/wrapper/VisionSensor.h"
#include "inu/wrapper/InertialSensor.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/auto/ArmAssemblyBuilder.h"
#include "pros/colors.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
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


		ArmAssemblyBuilder armBuilder;
		armBuilder.SetArmMotor(18, PIDProfile(0.7f));
		armBuilder.SetClawMotor(1);
		armBuilder.SetArmMaximumVelocity(40);
		std::shared_ptr<ArmAssembly> armAssembly = armBuilder.Build();

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
		while(true) {
			follower->FollowLine(700);
			chassis->TurnA(180);
		}
	}
	catch(InuException e) {
		std::cout << Color::FG_RED << e.what() << Color::FG_DEFAULT << std::endl;
		throw std::runtime_error("InuException thrown");
	}
}
