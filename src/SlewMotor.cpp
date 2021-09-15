#include "SlewMotor.h"
#include "SlewSystem.h"

using namespace pros;

SlewMotor::SlewMotor(unsigned int port) {
	this->port = port;
	rate = 20;
	targetSpeed = 0;
	SlewSystem::EnrollMotor(this);
}

SlewMotor::~SlewMotor() {
	SlewSystem::RemoveMotor(this);
}

void SlewMotor::Set(int speed) {
	this->targetSpeed = speed;
}

void SlewMotor::SetRate(unsigned int rate) {
	this->rate = rate;
}

unsigned int SlewMotor::GetPort() const {
	return port;
}

unsigned int SlewMotor::GetRate() const {
	return rate;
}

int SlewMotor::GetTargetSpeed() const {
	return targetSpeed;
}

