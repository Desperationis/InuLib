#include "PIDMotor.h"
#include "BackgroundMotorSystem.h"

using namespace pros;

PIDMotor::PIDMotor(unsigned int port) : BackgroundMotor(port) {
	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);

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
	return target;
}

const PIDProfile PIDMotor::GetPID() const {
	return pidProfile;
}

bool PIDMotor::AtTarget(unsigned int error) const {
	Motor motor(GetPort());
	double encoderValue = motor.get_position();

	return target + error > encoderValue && target - error < encoderValue;
}

void PIDMotor::_Update() {
	// If the target is not set, don't update. This decision was made because
	// there is a strong chance that when this object is initialized, the
	// motor's position might be extremely high and force this to move it back
	// to 0, which is bad. Here we assume that the target value inputted is
	// delibrate.

	if(!targetSet)
		return;

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

