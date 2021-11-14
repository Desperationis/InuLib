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

void XLineFollower::FollowLine() {
	while(LineDetected()) {
		if(center.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30, 0);
		}
		else if(left.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30, -6);
		}

		else if(right.IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(30, 6);
		}

		pros::delay(10);
	}

	Stop();
}

bool XLineFollower::LineDetected() {
	return right.IsLine(lightThreshold, activeOnDark) ||
		center.IsLine(lightThreshold, activeOnDark) ||
		left.IsLine(lightThreshold, activeOnDark);
}

std::int32_t XLineFollower::RecommendThreshold() {
	// Get darkest value (highest)
	std::int32_t darkVal = std::max({
			right.GetValue(), 
			left.GetValue(),
			center.GetValue()
		});
	
	// Get lightest value
	std::int32_t whiteVal = std::min({
			right.GetValue(), 
			left.GetValue(),
			center.GetValue()
		});

	// Get the midpoint between the values; This is the optimal threshold
	std::int32_t midpoint = (darkVal + whiteVal) / 2;

	return midpoint;
}


void XLineFollower::Stop() {
	chassis->Stop();
}
