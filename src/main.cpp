#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
#include "inu/Logo.hpp"
#include "inu/motor/background/PIDVisionMotor.h"
#include "inu/motor/background//SlewMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoXChassisBuilder.h"
#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/wrapper/InertialSensor.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/auto/ArmAssemblyBuilder.h"
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
void initialize() {
	//pros::lcd::initialize();
	inu::Logo::Draw();
	

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
		int port = 4;
		std::cout << Color::FG_GREEN << port << Color::FG_DEFAULT << std::endl;
		InertialSensor sensor(port); 


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

		AutoXChassisBuilder builder;
		builder.SetMotors(11,20,3,4);
		builder.SetGyro(10, gyroOptions);
		builder.SetChassisOptions(chassisOptions);

		std::shared_ptr<AutoXChassis> chassis = builder.Build();
		chassis->Turn(-1000);
		chassis->Turn(1000);
		chassis->TurnA(360);
		chassis->TurnA(-360);

		while(true) {
			pros::delay(10);
		}

		XLineFollowerBuilder followerBuilder;
		followerBuilder.SetSensors( { 'B', 'F', 'G', 'H', 'C'} );
		followerBuilder.SetSensorError( { -500, -190, 0, 60, -400 } );
		followerBuilder.SetChassis(std::weak_ptr(chassis));
		followerBuilder.ActivateOnDark(false);
		followerBuilder.SetLightThreshold(350);

		std::shared_ptr<XLineFollower> follower = followerBuilder.Build();
		follower->FollowLine(500);
	}
	catch(InuException e) {
		std::cout << Color::FG_RED << e.what() << Color::FG_DEFAULT << std::endl;
		throw std::runtime_error("InuException thrown");
	}
}
