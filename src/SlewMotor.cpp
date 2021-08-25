#include "SlewMotor.h"
#include "SlewSystem.h"

using namespace pros;

SlewMotor::SlewMotor(unsigned int port) {
	this->port = port;
}

void SlewMotor::Set(unsigned int speed) {
	this->targetSpeed = speed;
}

void SlewMotor::SetRate(unsigned int rate) {
	this->rate = rate;
}

unsigned int SlewMotor::GetPort() {
	return port;
}

unsigned int SlewMotor::GetRate() {
	return rate;
}

unsigned int SlewMotor::GetTargetSpeed() {
	return targetSpeed;
}

