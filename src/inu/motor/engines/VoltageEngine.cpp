#include "inu/motor/engines/VoltageEngine.h"

using namespace inu::engine;

VoltageEngine::VoltageEngine(inu::port motorPort) : motor(motorPort) {


}

void VoltageEngine::SetTarget(double value) {
	target = value;
}

void VoltageEngine::Execute() {
	motor.Move(target);
}

