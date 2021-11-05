#include "BackgroundMotorSystem.h"

using namespace pros;

BackgroundMotorSystem* BackgroundMotorSystem::instance = nullptr;

BackgroundMotorSystem* BackgroundMotorSystem::Instance() {
	if(instance == nullptr) {
		instance = new BackgroundMotorSystem();
	}

	return instance;
}

BackgroundMotorSystem::BackgroundMotorSystem() {
	backgroundTask = new Task(BackgroundTask, NULL, "BackgroundMotors");
	delay = 20;

	for(size_t i = 0; i < motors.max_size(); i++) {
		motors[i] = nullptr;
	}
}

void BackgroundMotorSystem::BackgroundTask(void* parameters) {
	while(true) {
		for(auto motor : motors) {
			if(motor != nullptr) {
				motor->_Update();
			}
		}

		pros::delay(delay);
	}
}

void BackgroundMotorSystem::SetDelay(unsigned int delay) {
	this->delay = delay;
}

void BackgroundMotorSystem::EnrollMotor(BackgroundMotor* motor) {
	size_t index = motor->GetPort() - 1;

	if(motors[index] == nullptr) {
		motors[index] = motor;
	}
}

void BackgroundMotorSystem::RemoveMotor(BackgroundMotor* motor) {
	// Make sure it exists here to delete it
	for(size_t i = 0; i < motors.max_size(); i++) {
		if(motors[i] == motor) {
			RemoveMotor(motor->GetPort());
			break;
		}
	}
}

void BackgroundMotorSystem::RemoveMotor(unsigned int port) {
	size_t index = port - 1;

	delete motors[index];
	motors[index] = nullptr;
}

