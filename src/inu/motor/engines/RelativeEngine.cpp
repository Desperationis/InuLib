#include "inu/motor/engines/RelativeEngine.h"

using namespace inu::engine;

RelativeEngine::RelativeEngine(inu::port motorPort) : Engine(motorPort) {
	maxSpeed = 127;
}

void RelativeEngine::SetMaxSpeed(uint8_t speed) {
	maxSpeed = speed;
}

void RelativeEngine::Execute() {
	motor.MoveRelative(target, maxSpeed);
}

