#include "inu/motor/engines/VoltageEngine.h"

using namespace inu::engine;

VoltageEngine::VoltageEngine(inu::port motorPort) : Engine(motorPort) {


}

void VoltageEngine::Execute() {
	motor.Move(target);
}

