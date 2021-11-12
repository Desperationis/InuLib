#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/auto/chassis/AutoXChassis.h"

using namespace inu;

XLineFollower::XLineFollower(XLineFollowerBuilder* builder) : 
	left(builder->GetLeftSensor()),
	center(builder->GetCenterSensor()),
	right(builder->GetRightSensor()) {

	chassis = builder->GetChassis();
	activeOnDark = builder->IsActiveOnDark();	
	lightThreshold = builder->GetLightThreshold();

	left.SetError(builder->GetLeftSensorError());
	center.SetError(builder->GetCenterSensorError());
	right.SetError(builder->GetRightSensorError());
}

void XLineFollower::Recenter() {
	while(!center.IsLine(lightThreshold, activeOnDark)) {
		if(left.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30, 6);
		}

		else if(right.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30,6);
		}

		pros::delay(10);
	}
}

void XLineFollower::FollowLine() {
	while(LineDetected()) {
		if(center.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30, 0);
		}
		else {
			Recenter();
		}

		pros::delay(10);
	}
}

bool XLineFollower::LineDetected() {
	return right.IsLine(lightThreshold, activeOnDark) ||
		center.IsLine(lightThreshold, activeOnDark) ||
		left.IsLine(lightThreshold, activeOnDark);
}

std::int32_t XLineFollower::DebugCalibrate() {
	// Assume that left and right are facing background and center is facing
	// the line.

	// Get the midpoint between the values
	std::int32_t darkAvg = (left.GetValue() + right.GetValue()) / 2;
	std::int32_t midpoint = (darkAvg + center.GetValue()) / 2;

	pros::lcd::print(3, "Left: %d", (int)left.GetValue());
	pros::lcd::print(4, "Center: %d", (int)center.GetValue());
	pros::lcd::print(5, "Right: %d", (int)right.GetValue());

	return midpoint;
}


void XLineFollower::Stop() {
	chassis->Stop();
}
