#include "SlewSystem.h"
#include "SlewMotor.h"

using namespace pros;

Task* SlewSystem::slewTask = nullptr;
std::vector<SlewMotor*> SlewSystem::motorVector;
unsigned int SlewSystem::delay = 20;

void SlewSystem::Start() {
	if(!IsRunning()) {
		motorVector.reserve(10);
		slewTask = new Task(SlewTask, NULL, "SlewTask");
	}
}

void SlewSystem::SlewTask(void* parameters) {
	while(IsRunning()) {
		for(int i = 0; i < motorVector.size(); i++) {
			auto motor = motorVector[i];

			// TODO: interpolate between values
		}

		pros::delay(SlewSystem::delay);
	}
}

void SlewSystem::SetDelay(unsigned int delay) {
	SlewSystem::delay = delay;
}

void SlewSystem::EnrollMotor(SlewMotor* motor) {
	// TODO: Turn motorVector into a map to prevent
	// same motor being used twice
	motorVector.push_back(motor);
}

void SlewSystem::RemoveMotor(SlewMotor* motor) {
	// if motor exists
	//		remove
}

bool SlewSystem::IsRunning() {
	return false;
}

void SlewSystem::Stop() {
	motorVector.clear();
}


