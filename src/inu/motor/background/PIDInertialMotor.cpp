#include "inu/motor/background/PIDInertialMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include "pros/llemu.hpp"
#include <algorithm>

using namespace inu;

PIDInertialMotor::PIDInertialMotor(unsigned int motorPort, unsigned int gyro,
		const PIDProfile& profile) : BackgroundMotor(motorPort),
		motor(motorPort), gyro(gyro), pid(-127, 127, profile) {

	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);
}

PIDInertialMotor::~PIDInertialMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void PIDInertialMotor::Set(double target) {
	pid.SetTarget(target);
}


void PIDInertialMotor::SetPID(const PIDProfile& pidProfile) {
	pid.SetPID(pidProfile);
}

double PIDInertialMotor::GetTarget() const {
	return pid.GetTarget();
}

const PIDProfile PIDInertialMotor::GetPID() const {
	return pid.GetPID();
}

bool PIDInertialMotor::AtTarget(unsigned int error) const {
	double angle = gyro.get_rotation();
	return pid.WithinError(angle, error);
}

void PIDInertialMotor::SetMaximumVelocity(unsigned int velocity) {
	pid.SetRange(-(int)velocity, (int)velocity);
}

bool PIDInertialMotor::IsReversed() const {
	return motor.IsReversed();
}

void PIDInertialMotor::_Update() {
	double motorSpeed = pid.Update(gyro.get_rotation());
	motor.Move(motorSpeed);
}

