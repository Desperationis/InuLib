#include "inu/motor/engines/EncoderEngine.h"

using namespace inu::engine;

EncoderEngine::EncoderEngine(inu::port motorPort, COORD mode, EncoderEngineSettings settings) : Engine(motorPort) {
	this->mode = mode;
	this->settings = settings;
}

void EncoderEngine::Execute() {
	if (mode == COORD::ABSOLUTE)
		motor.MoveAbsolute(target, settings.maxVelocity);
	else if (mode == COORD::RELATIVE)
		motor.MoveRelative(target, settings.maxVelocity);

	lastExecute.Mark();

	if(!settings.runInBackground)
		Wait();
}

bool EncoderEngine::InSteady() {
	return motor.IsSettled(settings.steadyError);
}

bool EncoderEngine::IsFinished() {
	auto elapsed = lastExecute.GetElapsed();

	if (elapsed > settings.timeout * 1000) 
		return true;

	return InSteady();
}

void EncoderEngine::Wait() {
	while(!IsFinished()) {
		pros::delay(10);
	}
}
