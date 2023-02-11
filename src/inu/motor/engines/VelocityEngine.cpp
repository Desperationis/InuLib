#include "inu/motor/engines/VelocityEngine.h"

using namespace inu::engine;

VelocityEngine::VelocityEngine(inu::port motorPort) : Engine(motorPort) {


}

void VelocityEngine::Execute() {
	motor.MoveVelocity(target);
}

