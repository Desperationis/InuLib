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

	leftError = builder->GetLeftSensorError();
	centerError = builder->GetCenterSensorError();
	rightError = builder->GetRightSensorError();
}

void XLineFollower::Recenter() {
	// Work on this
	while(LineDetected()) {
		if(!IsLine(center.get_value() - centerError)) {
			if(IsLine(left.get_value() - leftError)) {
				chassis->StrafeLeft(50);
			}

			else if(IsLine(right.get_value() - rightError)) {
				chassis->StrafeRight(50);
			}
		}
		else {
			chassis->Forward(400);
		}

		pros::delay(10);
	}
}


bool XLineFollower::LineDetected() {
	return IsLine(left.get_value() - leftError) ||
		IsLine(center.get_value() - centerError) ||
		IsLine(right.get_value() - rightError);
}

bool XLineFollower::IsLine(std::int32_t light) {
	// Lighter colors have a value closer to 0
	if(activeOnDark) {
		return light >= lightThreshold;
	}
	
	return light <= lightThreshold;
}

void XLineFollower::FollowLine() {

}


std::int32_t XLineFollower::DebugCalibrate() {
	// Assume that left and right are facing background and center is facing
	// the line.
	std::int32_t leftLight = left.get_value() - leftError;
	std::int32_t centerLight = center.get_value() - centerError;
	std::int32_t rightLight = right.get_value() - rightError;


	// Get the midpoint between the values
	std::int32_t darkAvg = (leftLight + rightLight) / 2;
	std::int32_t midpoint = (darkAvg + centerLight) / 2;

	return midpoint;
}


void XLineFollower::Stop() {
	chassis->Stop();
}
