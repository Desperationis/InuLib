#include "SlewSystem.h"
#include "SlewMotor.h"

using namespace pros;

std::vector<SlewMotor*> SlewSystem::motorVector;
Task* SlewSystem::slewTask = nullptr;
unsigned int SlewSystem::delay = 20;
bool SlewSystem::running = false;

void SlewSystem::Start() {
	// Start slew task if not started yet
	if(!IsRunning()) {
		running = true;
		motorVector.reserve(10);
		slewTask = new Task(SlewTask, NULL, "SlewTask");
	}
}

void SlewSystem::SlewTask(void* parameters) {
	while(IsRunning()) {
		for(int i = 0; i < motorVector.size(); i++) {
			SlewMotor* motor = motorVector[i];

			// TODO: interpolate between values
			Motor temp(motor->GetPort());
			int currentSpeed = temp.get_voltage();
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
	// TODO: Turn motorVector into a map to prevent
	// same motor being used twice
	motorVector.push_back(motor);
}

void SlewSystem::RemoveMotor(SlewMotor* motor) {
	// if motor exists
	//		remove
}

bool SlewSystem::IsRunning() {
	return running;
}

void SlewSystem::Stop() {
	motorVector.clear();
	running = false;
}

unsigned int Interpolate(unsigned int start, unsigned int end,
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



