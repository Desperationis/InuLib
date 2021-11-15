#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include <algorithm>

using namespace inu;

PIDMotor::PIDMotor(unsigned int port) : BackgroundMotor(port), motor(port) {
	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);

	SetMaximumVelocity(127);
	proportion = 0;
	integral = 0;
	derivative = 0;
	pastError = 0;

	targetSet = false;
}

PIDMotor::~PIDMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void PIDMotor::Set(int target) {
	this->target = target;
	targetSet = true;
}


void PIDMotor::SetPID(PIDProfile pidProfile) {
	this->pidProfile = pidProfile;
}

int PIDMotor::GetTarget() const {
	if(reversed)
		return -target;
	return target;
}

void PIDMotor::SetReversed(bool reverse) {
	this->reversed = reverse;
}

const PIDProfile PIDMotor::GetPID() const {
	return pidProfile;
}

bool PIDMotor::AtTarget(unsigned int error) const {
	return motor.IsSettled(error);
}

void PIDMotor::SetMaximumVelocity(unsigned int velocity) {
	maxVelocity = std::clamp<int>(velocity, -127, 127);
}

void PIDMotor::_Update() {
	// If the target is not set, don't update. This decision was made because
	// there is a strong chance that when this object is initialized, the
	// motor's position might be extremely high and force this to move it back
	// to 0, which is bad. Here we assume that the target value inputted is
	// delibrate.

	if(!targetSet)
		return;

	double encoderValue = motor.GetPosition();

	proportion = GetTarget() - encoderValue; 
	integral += proportion; 
	derivative = proportion - pastError;
	pastError = proportion;

	if(abs((int)proportion) < 5) {
		integral = 0;
	}

	if(proportion > 12000) {
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

