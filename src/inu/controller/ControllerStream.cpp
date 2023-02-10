#include "inu/controller/ControllerStream.h"
#include "pros/misc.h"

using namespace pros;
using namespace inu;

std::map<controller_id_e_t, const char*> ControllerStream::requestMap;
std::map<controller_id_e_t, const char*> ControllerStream::printedMap;
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
	requestMap[controllerID] = content;
	if(printedMap.find(controllerID) == printedMap.end()) {
		printedMap[controllerID] = "";
	}
}

void ControllerStream::PrintTask(void* parameters) {
	while(IsRunning()) {
		for(auto it : requestMap) {
			controller_id_e_t controllerID = it.first;
			const char* message = it.second;
			Controller controller(controllerID);

			if(message != nullptr && message != printedMap[controllerID]) {
				controller.print(0,0, message);
				printedMap[controllerID] = message;
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
