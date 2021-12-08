#include "inu/auto/XLineFollower.h"
#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/wrapper/ADIMotor.h"
#include "inu/wrapper/LineSensor.h"
#include "inu/InuException.hpp"

using namespace inu;

XLineFollower::XLineFollower(const XLineFollowerBuilder& builder) {
	chassis = builder.GetChassis().lock(); // TODO: Error handle this
	activeOnDark = builder.IsActiveOnDark();	
	lightThreshold = builder.GetLightThreshold();
	
	auto sensorPorts = builder.GetSensors();
	auto sensorErrors = builder.GetSensorErrors();

	for(std::size_t i = 0; i < sensorPorts.max_size(); i++) {
		auto port = sensorPorts[i];
		lightSensors[i] = std::unique_ptr<inu::LineSensor>(new inu::LineSensor(port));
		lightSensors[i]->SetError(sensorErrors[i]);
	}
}

void XLineFollower::FollowLine(unsigned int velocity) {
	auto& leftest = lightSensors[0];
	auto& left = lightSensors[1];
	auto& center = lightSensors[2];
	auto& right = lightSensors[3];
	auto& rightest = lightSensors[4];

	if(velocity > 300)
		throw InuException("XLineFollower: FollowLine() was passed in a velocity greater than 300; Maybe you meant FollowLine(distance)?");

	while(LineDetected()) {
		if(center->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 0);
		}
		else if(left->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, -6);
		}

		else if(right->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 6);
		}

		else if(leftest->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, -6);
		}

		else if(rightest->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 6);
		}

		pros::delay(10);
	}

	Stop();
}

void XLineFollower::FollowLine(unsigned int distance, unsigned int velocity) {
	auto& leftest = lightSensors[0];
	auto& left = lightSensors[1];
	auto& center = lightSensors[2];
	auto& right = lightSensors[3];
	auto& rightest = lightSensors[4];

	auto OGdirection = chassis->GetAbsoluteRotation();
	chassis->TareDistance();

	while(chassis->GetDistance() < distance) {
		if(center->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 0);
		}
		else if(left->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, -6);
		}

		else if(right->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 6);
		}

		else if(leftest->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, -6);
		}

		else if(rightest->IsLine(lightThreshold, activeOnDark)) {
			chassis->Swerve(velocity, 6);
		}

		pros::delay(10);
	}

	//chassis->TurnAbsolute(OGdirection);

	Stop();
}

bool XLineFollower::LineDetected() {
	for(std::size_t i = 0; i < lightSensors.size(); i++) {
		if(lightSensors[i]->IsLine(lightThreshold, activeOnDark))
				return true;
	}

	return false;
}

std::int32_t XLineFollower::RecommendThreshold() {
	auto& left = lightSensors[2];
	auto& center = lightSensors[3];
	auto& right = lightSensors[4];

	// Get darkest value (highest)
	std::int32_t darkVal = std::max({
			right->GetValue(), 
			left->GetValue(),
			center->GetValue()
		});
	
	// Get lightest value
	std::int32_t whiteVal = std::min({
			right->GetValue(), 
			left->GetValue(),
			center->GetValue()
		});

	// Get the midpoint between the values; This is the optimal threshold
	std::int32_t midpoint = (darkVal + whiteVal) / 2;

	for(std::size_t i = 0; i < lightSensors.size(); i++) {
		pros::lcd::print(i, "Sensor %i value: %i", i, lightSensors[i]->GetValue());
	}	

	return midpoint;
}


void XLineFollower::Stop() {
	chassis->Stop();
}