#include "inu/motor/background/PIDInertialMotor.h"
#include "inu/background/BackgroundSystem.h"
#include "pros/llemu.hpp"
#include <algorithm>

using namespace inu;

PIDInertialMotor::PIDInertialMotor(inu::port motorPort, inu::port gyro, const PIDProfile& profile) : 
	BackgroundTask(motorPort), motor(motorPort), gyro(gyro), pid(-127, 127, profile) {

	this->port = port;
	BackgroundSystem::Instance()->EnrollTask(this);
}

PIDInertialMotor::~PIDInertialMotor() {
	BackgroundSystem::Instance()->RemoveTask(this);
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
	return pid.WithinError(angle, (int)error);
}

void PIDInertialMotor::SetMaximumVelocity(int velocity) {
	pid.SetRange(-velocity, velocity);
}

bool PIDInertialMotor::IsReversed() const {
	return motor.IsReversed();
}

void PIDInertialMotor::_Update() {
	if(pid.TargetSet()) {
		double motorSpeed = pid.Update(gyro.get_rotation());
		motor.MoveVelocity(motorSpeed);
	}
	else {
		motor.MoveVelocity(0);
	}
}

