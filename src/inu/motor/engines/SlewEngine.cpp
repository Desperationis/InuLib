#include "inu/motor/engines/SlewEngine.h"
#include "inu/background/BackgroundSystem.h"

using namespace inu::engine;

SlewEngine::SlewEngine(inu::port motorPort) : Engine(motorPort), BackgroundTask(motorPort) {
	slewRate = 20;
	target = 0;
	enrolled = false;
}

SlewEngine::~SlewEngine() {
	this->Shutdown();
}

void SlewEngine::Execute() {
	if (!enrolled) {
		BackgroundSystem::Instance()->EnrollTask(this);
		enrolled = true;
	}
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

void SlewEngine::Shutdown() {
	Engine::Shutdown();

	if(enrolled) {
		BackgroundSystem::Instance()->RemoveTask(this);
		enrolled = false;
	}
}

void SlewEngine::_Update() {
	int currentSpeed = motor.GetVoltage();
	motor.Move(Interpolate(currentSpeed, target, slewRate));
}
