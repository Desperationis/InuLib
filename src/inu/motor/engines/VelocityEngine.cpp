#include "inu/motor/engines/VelocityEngine.h"

using namespace inu::engine;

VelocityEngine::VelocityEngine(inu::port motorPort) : motor(motorPort) {


}

void VelocityEngine::SetTarget(double value) {
	target = value;
}

void VelocityEngine::Execute() {
	motor.MoveVelocity(target);
}

