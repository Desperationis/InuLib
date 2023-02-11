#include "inu/motor/engines/SlewEngine.h"
#include "inu/background/BackgroundSystem.h"

using namespace inu::engine;

SlewEngine::SlewEngine(inu::port motorPort) : motor(motorPort), BackgroundTask(motorPort) {
	slewRate = 20;
	target = 0;
	BackgroundSystem::Instance()->EnrollTask(this);

}

SlewEngine::~SlewEngine() {
	BackgroundSystem::Instance()->RemoveTask(this);
}

void SlewEngine::SetTarget(double value) {
	target = value;
}

void SlewEngine::Execute() {
	motor.Move(target);
}

int SlewEngine::Interpolate(int start, int end, unsigned int maximum) {
	// Calculate remaining speed to interpolate
	int difference = end - start;

	// If the difference is too large, cap out difference
	if(abs(difference) > maximum) {
		int sign = difference > 0 ? 1 : (difference < 0 ? -1 : 0);
		return start + (sign * maximum);
	}

	return end;
}

void SlewEngine::SetSlewRate(uint8_t rate) {
	slewRate = rate;
}

void SlewEngine::_Update() {
	int currentSpeed = motor.GetVoltage();
	motor.Move(Interpolate(currentSpeed, target, slewRate));
}
