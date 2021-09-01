#include "PIDSystem.h"
#include "PIDMotor.h"
#include "pros/llemu.hpp"

using namespace pros;

std::map<unsigned int, PIDMotor*> PIDSystem::motorMap;
Task* PIDSystem::PIDtask = nullptr;
unsigned int PIDSystem::delay = 10;
bool PIDSystem::running = false;

void PIDSystem::Start() {
	// Start slew task if not started yet
	if(!IsRunning()) {
		running = true;
		PIDtask = new Task(PIDTask, NULL, "PIDTask");
	}
}

void PIDSystem::PIDTask(void* parameters) {
	while(IsRunning()) {
		for(auto it : motorMap) {
			PIDMotor* motor = it.second;
			motor->_UpdatePID();
		}

		pros::delay(PIDSystem::delay);
	}
}

void PIDSystem::SetDelay(unsigned int delay) {
	PIDSystem::delay = delay;
}

void PIDSystem::EnrollMotor(PIDMotor* motor) {
	if(motorMap.find(motor->GetPort()) == motorMap.end()) {
		motorMap[motor->GetPort()] = motor;
	}
}

void PIDSystem::RemoveMotor(PIDMotor* motor) {
	motorMap.erase(motor->GetPort());	
}

bool PIDSystem::IsRunning() {
	return running;
}

void PIDSystem::Stop() {
	motorMap.clear();
	running = false;
}

