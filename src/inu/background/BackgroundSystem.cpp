#include "inu/background/BackgroundSystem.h"

using pros::Task;
using namespace inu;

BackgroundSystem* BackgroundSystem::instance = nullptr;

BackgroundSystem* BackgroundSystem::Instance() {
	if(instance == nullptr) {
		instance = new BackgroundSystem();
	}

	return instance;
}

void BMSBackgroundFunc(void* parameters) {
	// Wrapper function for Background Task; This is needed as PROS only allows
	// compile-time functions to be run.
	BackgroundSystem::Instance()->BackgroundSystemTask(parameters);
}

BackgroundSystem::BackgroundSystem() {
	backgroundTask = new Task(BMSBackgroundFunc, NULL, "BackgroundTasks");
	delay = 20;

	for(size_t i = 0; i < tasks.max_size(); i++) {
		tasks[i] = nullptr;
	}
}

void BackgroundSystem::BackgroundSystemTask(void* parameters) {
	while(true) {
		for(auto task : tasks) {
			if(task != nullptr) {
				task->_Update();
			}
		}

		pros::delay(delay);
	}
}

void BackgroundSystem::SetDelay(unsigned int delay) {
	this->delay = delay;
}

unsigned int BackgroundSystem::GetDelay() {
	return delay;
}

void BackgroundSystem::EnrollTask(BackgroundTask* task) {
	size_t index = task->GetPort() - 1;

	if(!TaskExists(task->GetPort())) {
		tasks[index] = task;
	}
}

void BackgroundSystem::RemoveTask(BackgroundTask* task) {
	// Make sure it exists here to delete it
	for(size_t i = 0; i < tasks.max_size(); i++) {
		if(tasks[i] == task) {
			RemoveTask(task->GetPort());
			break;
		}
	}
}

bool BackgroundSystem::TaskExists(inu::port port) {
	return tasks[port - 1] != nullptr;
}

void BackgroundSystem::RemoveTask(inu::port port) {
	// Never call delete here; we don't own the pointers
	tasks[port - 1] = nullptr;
}

