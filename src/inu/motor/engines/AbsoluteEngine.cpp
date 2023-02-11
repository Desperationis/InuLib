#include "inu/motor/engines/AbsoluteEngine.h"

using namespace inu::engine;

AbsoluteEngine::AbsoluteEngine(inu::port motorPort) : motor(motorPort) {
	maxSpeed = 127;
}

void AbsoluteEngine::SetTarget(double value) {
	target = value;
}

void AbsoluteEngine::SetMaxSpeed(uint8_t speed) {
	maxSpeed = speed;
}

void AbsoluteEngine::Execute() {
	motor.MoveAbsolute(target, maxSpeed);
}

