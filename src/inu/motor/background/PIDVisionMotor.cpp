#include "inu/motor/background/PIDVisionMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include "inu/wrapper/VisionSensor.h"
#include "pros/rtos.hpp"
#include "pros/vision.h"
#include <algorithm>

using namespace inu;

PIDVisionMotor::PIDVisionMotor(unsigned int motorPort, std::shared_ptr<VisionSensor> sensor1, std::shared_ptr<VisionSensor> sensor2) :
	BackgroundMotor(motorPort), motor(motorPort) {

	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);

	SetMaximumVelocity(127);
	proportion = 0;
	integral = 0;
	derivative = 0;
	pastError = 0;
	enabled = false;

	vision1 = sensor1;
	vision2 = sensor2;
}

PIDVisionMotor::~PIDVisionMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void PIDVisionMotor::Enable() {
	enabled = true;
}

void PIDVisionMotor::Disable() {
	enabled = false;
}

void PIDVisionMotor::SetPID(PIDProfile pidProfile) {
	this->pidProfile = pidProfile;
}

void PIDVisionMotor::SetReversed(bool reversed) {
	motor.SetReversed(reversed);
}

const PIDProfile PIDVisionMotor::GetPID() const {
	return pidProfile;
}

bool PIDVisionMotor::AtTarget(unsigned int error) const {
	auto biggestObject = vision1->GetLargestObject();
	if(biggestObject == nullptr) {
		biggestObject = vision2->GetLargestObject();
		if(biggestObject == nullptr) {
			return false;
		}
	}

	return std::abs(biggestObject->x_middle_coord) <= error;
}

void PIDVisionMotor::SetMaximumVelocity(unsigned int velocity) {
	maxVelocity = std::clamp<int>(velocity, -127, 127);
}

bool PIDVisionMotor::IsReversed() const {
	return motor.IsReversed();
}

void PIDVisionMotor::_Update() {
	// If the target is not set, don't update. This decision was made because
	// there is a strong chance that when this object is initialized, the
	// motor's position might be extremely high and force this to move it back
	// to 0, which is bad. Here we assume that the target value inputted is
	// delibrate.

	if(!enabled)
		return;

	auto biggestObject = vision1->GetLargestObject();
	double difference = 0;

	if(biggestObject == nullptr) {
		motor.Move(0);
		return;
	}
	else 
		difference = vision1->GetCenterOffsetX(*biggestObject);

	proportion = difference; 
	integral += proportion; 
	derivative = proportion - pastError;
	pastError = proportion;

	if(abs((int)proportion) < 2) { // CHANGE
		integral = 0;
	}

	if(std::abs(proportion) > 180) {
		// Tune this
		integral = 0;
	}

	float p = pidProfile.p;
	float i = pidProfile.i;
	float d = pidProfile.d;

	float motorSpeed = (proportion * p) + (integral * i) + (derivative * d);
	motorSpeed = std::clamp<int>(motorSpeed, -maxVelocity, maxVelocity);

	motor.Move(motorSpeed);
}

