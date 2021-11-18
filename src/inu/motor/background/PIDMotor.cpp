#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include <algorithm>

using namespace inu;

PIDMotor::PIDMotor(unsigned int port, const PIDProfile& profile) :
	BackgroundMotor(port), motor(port), pid(-127, 127, profile) {

	this->port = port;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);
}

PIDMotor::~PIDMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void PIDMotor::Set(int target) {
	pid.SetTarget(target);
}

void PIDMotor::SetPID(const PIDProfile& pidProfile) {
	pid.SetPID(pidProfile);
}

int PIDMotor::GetTarget() const {
	return pid.GetTarget();
}

bool PIDMotor::AtTarget(unsigned int error) const {
	return motor.IsSettled(error);
}

void PIDMotor::SetMaximumVelocity(unsigned int velocity) {
	pid.SetRange(-(int)velocity, (int)velocity);
}

void PIDMotor::_Update() {
	double motorSpeed = pid.Update(motor.GetPosition());
	motor.Move(motorSpeed);
}

