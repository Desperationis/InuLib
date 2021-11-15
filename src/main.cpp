#include "main.h"
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
	pros::lcd::initialize();

	// This delay is REQUIRED for the program to work; Without this, core
	// components may or may not be initialized (i.e. inertial sensor) and 
	// return wicked weird values like NaN
	pros::delay(3000);
}

void CalibrateThreshold() {
	AutoXChassisBuilder builder;
	builder.SetMotors(11,20,3,4);
	std::shared_ptr<AutoXChassis> chassis = builder.Build();

	XLineFollowerBuilder followerBuilder;
	followerBuilder.SetSensors(6,7,8);
	followerBuilder.SetSensorError(250,0,0);
	followerBuilder.SetChassis(std::weak_ptr(chassis));
	std::shared_ptr<XLineFollower> follower = followerBuilder.Build();

	// Calibration code
	while(true) {
		bool detected = follower->LineDetected();
		pros::lcd::print(0, "Line detected: %d", (int)detected);

		int value = follower->RecommendThreshold();
		pros::lcd::print(1, "Recommended midpoint: %d", (int) value);
		pros::delay(10);
	}
}

void opcontrol() {
	/*ArmAssemblyBuilder armBuilder;
	armBuilder.SetArmMotor(18);
	armBuilder.SetClawMotor(1);
	armBuilder.SetArmPIDProfile(PIDProfile(0.6f));
	armBuilder.SetArmMaximumVelocity(40);

	std::shared_ptr<ArmAssembly> armAssembly = armBuilder.Build();

	armAssembly->SetArm(-500);
	pros::delay(10000);
	armAssembly->Grab();
	armAssembly->Release();*/

	/*
	PIDProfile p;
	p.p = 0.9;
	p.i = 0.15;
	p.d = 0;

	AutoXChassisBuilder builder;
	builder.SetMaxVelocity(60); 
	builder.SetMotors(11,20,3,4);
	builder.SetGyro(10);
	builder.SetTimeout(10);
	builder.SetGyroPID(p);
	builder.SetMaxAngleError(5); 
	builder.SetStalling(true);
	builder.SetTimeoutAlignLimit(0.5); // Makes a HUGE difference

	std::shared_ptr<AutoXChassis> chassis = builder.Build();
	chassis->TurnA(360);

	XLineFollowerBuilder followerBuilder;
	followerBuilder.SetSensors(6,7,8);
	followerBuilder.SetSensorError(250,0,0);
	followerBuilder.SetChassis(std::weak_ptr(chassis));
	followerBuilder.ActivateOnDark(false);
	//followerBuilder.SetLightThreshold(500);
	followerBuilder.SetLightThreshold(1500);

	std::shared_ptr<XLineFollower> follower = followerBuilder.Build();
	while(true) {
		follower->FollowLine();
		//pros::lcd::print(6, "Rec: %i", (int)follower->RecommendThreshold());
		pros::delay(20);
	} // CAMERA

	*/
	
	auto JENGA = pros::Vision::signature_from_utility(1, 1561, 2319, 1940, -1525, -911, -1218, 3.000, 0);

	std::shared_ptr<VisionSensor> vision(new VisionSensor(9)); // right
	std::shared_ptr<VisionSensor> vision2(new VisionSensor(12)); // left
	vision->SetExposure(58);
	vision2->SetExposure(58);
	vision->SetSignature(1, &JENGA);
	vision2->SetSignature(1, &JENGA);
	vision->SetMinimumArea(80);
	vision2->SetMinimumArea(80);
	vision->SetCenterPoint(200, 30);
	vision2->SetCenterPoint(200, 30);

	inu::PIDVisionMotor tl(11, vision2, vision2);
	inu::PIDVisionMotor tr(20, vision2, vision2);
	inu::PIDVisionMotor bl(3, vision2, vision2);
	inu::PIDVisionMotor br(4, vision2, vision2);

	tl.SetMaximumVelocity(40);
	tr.SetMaximumVelocity(40);
	bl.SetMaximumVelocity(40);
	br.SetMaximumVelocity(40);

	tl.Enable();
	tr.Enable();
	bl.Enable();
	br.Enable();

	PIDProfile t;
	t.p = 0.3;

	tl.SetPID(t);
	tr.SetPID(t);
	bl.SetPID(t);
	br.SetPID(t);

	while(true) {
		auto leftLargestObject = vision2->GetLargestObject();
		if(leftLargestObject != nullptr) {
			pros::lcd::print(0, "Left: %i %i", leftLargestObject->x_middle_coord, leftLargestObject->y_middle_coord);
			pros::lcd::print(1, "Left X Dif: %i", vision->GetCenterOffsetX(*leftLargestObject));
		}
		pros::delay(10);
	}


}
