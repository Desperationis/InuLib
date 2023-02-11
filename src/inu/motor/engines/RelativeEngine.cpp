#include "inu/motor/engines/RelativeEngine.h"

using namespace inu::engine;

RelativeEngine::RelativeEngine(inu::port motorPort) : motor(motorPort) {
	maxSpeed = 127;
}

void RelativeEngine::SetTarget(double value) {
	target = value;
}

void RelativeEngine::SetMaxSpeed(uint8_t speed) {
	maxSpeed = speed;
}

void RelativeEngine::Execute() {
	motor.MoveRelative(target, maxSpeed);
}

