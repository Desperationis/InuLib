#include "inu/motor/background/PIDInertialMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include "inu/motor/Motor.hpp"
#include <algorithm>

using namespace inu;

PIDInertialMotor::PIDInertialMotor(unsigned int motorPort, unsigned int gyro) :
	BackgroundMotor(motorPort), motor(motorPort), gyro(gyro) {

	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);

	SetMaximumVelocity(127);
	proportion = 0;
	integral = 0;
	derivative = 0;
	pastError = 0;

	targetSet = false;
}

PIDInertialMotor::~PIDInertialMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void PIDInertialMotor::Set(double target) {
	this->target = target;
	targetSet = true;
}


void PIDInertialMotor::SetPID(PIDProfile pidProfile) {
	this->pidProfile = pidProfile;
}

void PIDInertialMotor::SetReversed(bool reversed) {
	motor.set_reversed(reversed);
}

double PIDInertialMotor::GetTarget() const {
	return target;
}

const PIDProfile PIDInertialMotor::GetPID() const {
	return pidProfile;
}

bool PIDInertialMotor::AtTarget(unsigned int error) const {
	double angle = gyro.get_rotation();
	return angle > target - error && angle < target + error;
}

void PIDInertialMotor::SetMaximumVelocity(unsigned int velocity) {
	maxVelocity = std::clamp<int>(velocity, -127, 127);
}

bool PIDInertialMotor::IsReversed() const {
	return motor.is_reversed();
}

void PIDInertialMotor::_Update() {
	// If the target is not set, don't update. This decision was made because
	// there is a strong chance that when this object is initialized, the
	// motor's position might be extremely high and force this to move it back
	// to 0, which is bad. Here we assume that the target value inputted is
	// delibrate.

	if(!targetSet)
		return;

	double angleValue = gyro.get_rotation();

	proportion = target - angleValue; 
	integral += proportion; 
	derivative = proportion - pastError;
	pastError = proportion;

	if(abs((int)proportion) < 10) {
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

	motor.move(motorSpeed);
}

