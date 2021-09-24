#include "SlewSystem.h"
#include "SlewMotor.h"
#include "pros/llemu.hpp"

using namespace pros;

std::map<unsigned int, SlewMotor*> SlewSystem::motorMap;
Task* SlewSystem::slewTask = nullptr;
unsigned int SlewSystem::delay = 20;
bool SlewSystem::running = false;

void SlewSystem::Start() {
	// Start slew task if not started yet
	if(!IsRunning()) {
		running = true;
		slewTask = new Task(SlewTask, NULL, "SlewTask");
	}
}

void SlewSystem::SlewTask(void* parameters) {
	while(IsRunning()) {
		for(auto it : motorMap) {
			SlewMotor* motor = it.second;

			Motor temp(motor->GetPort());
			int currentSpeed = (temp.get_voltage() / 12000.0) * 127;
			int targetSpeed = motor->GetTargetSpeed();
			int maximumDif = motor->GetRate();

			temp.move(Interpolate(currentSpeed, targetSpeed, maximumDif));
		}

		pros::delay(SlewSystem::delay);
	}
}

void SlewSystem::SetDelay(unsigned int delay) {
	SlewSystem::delay = delay;
}

void SlewSystem::EnrollMotor(SlewMotor* motor) {
	if(motorMap.find(motor->GetPort()) == motorMap.end()) {
		motorMap[motor->GetPort()] = motor;
	}
}

void SlewSystem::RemoveMotor(SlewMotor* motor) {
	motorMap.erase(motor->GetPort());	
}

bool SlewSystem::IsRunning() {
	return running;
}

void SlewSystem::Stop() {
	motorMap.clear();
	running = false;
}

unsigned int SlewSystem::Interpolate(unsigned int start, unsigned int end,
		unsigned int maximum) {

	// Calculate remaining speed to interpolate
	short difference = end - start;

	// If the difference is too large, cap out difference
	if(abs(difference) > maximum) {
		int sign = difference > 0 ? 1 : (difference < 0 ? -1 : 0);
		return start + (sign * maximum);
	}

	return end;
}



