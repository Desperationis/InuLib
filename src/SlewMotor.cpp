#include "SlewMotor.h"
#include "BackgroundMotorSystem.h"

using namespace pros;

SlewMotor::SlewMotor(unsigned int port) : BackgroundMotor(port) {
	this->port = port;
	rate = 20;
	targetSpeed = 0;
	BackgroundMotorSystem::Instance()->EnrollMotor(this);
}

SlewMotor::~SlewMotor() {
	BackgroundMotorSystem::Instance()->RemoveMotor(this);
}

void SlewMotor::Set(int speed) {
	this->targetSpeed = speed;
}

void SlewMotor::SetRate(unsigned int rate) {
	this->rate = rate;
}

unsigned int SlewMotor::GetRate() const {
	return rate;
}

int SlewMotor::GetTargetSpeed() const {
	return targetSpeed;
}

unsigned int Interpolate(unsigned int start, unsigned int end,
		unsigned int maximum) {

	// Calculate remaining speed to interpolate
	short difference = end - start;

	// If the difference is too large, cap out difference
	if(abs(difference) > maximum) {
		int sign = difference > 0 ? 1 : (difference < 0 ? -1 : 0);
		return start + (sign * maximum);
	}

	return end;
}


void SlewMotor::_Update() {
	Motor temp(GetPort());
	int currentSpeed = (temp.get_voltage() / 12000.0) * 127;
	int targetSpeed = GetTargetSpeed();
	int maximumDif = GetRate();

	temp.move(Interpolate(currentSpeed, targetSpeed, maximumDif));
}
