#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Color.hpp"
#include "inu/Logo.hpp"
#include "inu/motor/background/PIDVisionMotor.h"
#include "inu/motor/background//SlewMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/auto/ArmAssemblyBuilder.h"
#include <memory>
#include <algorithm>


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
		ArmAssemblyBuilder armBuilder;
		armBuilder.SetArmMotor(18, PIDProfile(0.7f));
		armBuilder.SetClawMotor(1);
		armBuilder.SetArmMaximumVelocity(40);

		std::shared_ptr<ArmAssembly> armAssembly = armBuilder.Build();
		armAssembly->SetArm(-500);

		while(!armAssembly->AtTarget(10)) {
			pros::delay(10);
		}
		
		armAssembly->Grab();
		armAssembly->Release();
		armAssembly->SetArm(0);

		while(!armAssembly->AtTarget(10)) {
			pros::delay(10);
		}

		
		/*PIDProfile p;
		p.p = 0.9;
		p.i = 0.1;
		p.d = 0;
		p.integralWindupLimit = 50;
		p.integralLevelingError = 0;

		AutoXChassisBuilder builder;
		builder.SetMaxVelocity(60); 
		builder.SetMotors(11,20,3,4);
		builder.SetGyro(10, p);
		builder.SetTimeout(10);
		builder.SetMaxAngleError(5); 
		builder.SetStalling(true);
		builder.SetTimeoutAlignLimit(0.5); // Makes a HUGE difference

		std::shared_ptr<AutoXChassis> chassis = builder.Build();

		XLineFollowerBuilder followerBuilder;
		followerBuilder.SetSensors( { 'B', 'F', 'G', 'H', 'C'} );
		followerBuilder.SetSensorError( { -500, -190, 0, 60, -400 } );
		followerBuilder.SetChassis(std::weak_ptr(chassis));
		followerBuilder.ActivateOnDark(false);
		followerBuilder.SetLightThreshold(350);

		std::shared_ptr<XLineFollower> follower = followerBuilder.Build();*/
	}
	catch(InuException e) {
		std::cout << Color::FG_RED << e.what() << Color::FG_DEFAULT << std::endl;

		for(std::size_t i = 0; i < 10; i++) 
			pros::lcd::print(i, "InuException caught; Check Terminal.");
	}
}
