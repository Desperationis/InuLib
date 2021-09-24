#include "ControllerStream.h"
#include "pros/misc.h"

using namespace pros;

std::map<controller_id_e_t, const char*> ControllerStream::printMap;
std::map<controller_id_e_t, bool> ControllerStream::changeMap;
Task* ControllerStream::printTask = nullptr;
unsigned int ControllerStream::delay = 60;
bool ControllerStream::running = false;

void ControllerStream::Start() {
	// Start print task if not started yet
	if(!IsRunning()) {
		running = true;
		printTask = new Task(PrintTask, NULL, "PrintTask");
	}
}

void ControllerStream::Print(controller_id_e_t controllerID, const char* content) {
	if(changeMap.find(controllerID) == changeMap.end()) {
		changeMap[controllerID] = true;
	}
	else {
		changeMap[controllerID] = content != printMap[controllerID];
	}
	printMap[controllerID] = content;
}

void ControllerStream::PrintTask(void* parameters) {
	while(IsRunning()) {
		for(auto it : printMap) {
			controller_id_e_t controllerID = it.first;
			const char* message = it.second;
			Controller controller(controllerID);

			if(message != nullptr && changeMap[controllerID]) {
				controller.print(0,0, message);
				changeMap[controllerID] = false;
			}
		}
		pros::delay(ControllerStream::delay);
	}
}

void ControllerStream::SetDelay(unsigned int delay) {
	ControllerStream::delay = delay;
}

bool ControllerStream::IsRunning() {
	return running;
}

void ControllerStream::Stop() {
	running = false;
}
