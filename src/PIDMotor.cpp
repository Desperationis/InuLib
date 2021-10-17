#include "PIDMotor.h"
#include "PIDSystem.h"

using namespace pros;

PIDMotor::PIDMotor(unsigned int port) {
	this->port = port;
	PIDSystem::EnrollMotor(this);

	proportion = 0;
	integral = 0;
	derivative = 0;
	pastError = 0;
}

PIDMotor::~PIDMotor() {
	PIDSystem::RemoveMotor(this);
}

void PIDMotor::Set(int target) {
	this->target = target;
}


void PIDMotor::SetPID(PIDProfile pidProfile) {
	this->pidProfile = pidProfile;
}

unsigned int PIDMotor::GetPort() const {
	return port;
}

int PIDMotor::GetTarget() const {
	return target;
}

const PIDProfile PIDMotor::GetPID() const {
	return pidProfile;
}

void PIDMotor::_UpdatePID() {
	Motor motor(GetPort());
	double encoderValue = motor.get_position();

	proportion = target - encoderValue;
	integral += proportion;
	derivative = proportion - pastError;
	pastError = proportion;

	if(abs((int)proportion) < 20) {
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
	motor.move(motorSpeed);
}









