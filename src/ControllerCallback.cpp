#include "ControllerCallback.h"
#include "pros/misc.h"
#include "pros/rtos.h"

using namespace pros;

ControllerCallback::ControllerCallback(controller_id_e_t id) : controller(id) {
}


void ControllerCallback::AsyncCallback(controller_digital_e_t button, task_fn_t func) {
	if(callbackButtonMap.find(button) == callbackButtonMap.end()) {
		CallbackInfo callbackInfo;
		callbackInfo.async = true;
		callbackInfo.func = func;

		callbackButtonMap[button] = callbackInfo;
	}
}

void ControllerCallback::SyncCallback(controller_digital_e_t button, task_fn_t func) {
	if(callbackButtonMap.find(button) == callbackButtonMap.end()) {
		CallbackInfo callbackInfo;
		callbackInfo.async = false;
		callbackInfo.func = func;

		callbackButtonMap[button] = callbackInfo;
	}
}


void ControllerCallback::PollController() {
	for(int i = 0; i < DIGITAL.size(); i++) {
		controller_digital_e_t button = DIGITAL[i];

		if(callbackButtonMap.find(button) != callbackButtonMap.end()) {
			CallbackInfo cInfo = callbackButtonMap[button];

			if(controller.get_digital(button) && cInfo.buttonPressed == false) {
				// Sync Case
				if(cInfo.async == false) {
					cInfo.func(nullptr);
				}

				// Async Case
				else {
					if(GetTask(cInfo.func) != nullptr) {
						DeleteTask(cInfo.func);
					}
					Task* asyncTask = new Task(cInfo.func, nullptr, "");
					daemonMap[cInfo.func] = asyncTask;
				}
			}

			cInfo.buttonPressed = controller.get_digital(button);
		}
	}

}

pros::Task* ControllerCallback::GetTask(pros::task_fn_t func) {
	if(daemonMap.find(func) == daemonMap.end()) {
		return nullptr;
	}

	task_state_e_t taskState = (task_state_e_t)daemonMap[func]->get_state();

	if(taskState != E_TASK_STATE_READY && taskState != E_TASK_STATE_RUNNING) {
		return nullptr;
	}

	return daemonMap[func];
}



void ControllerCallback::DeleteTask(pros::task_fn_t func) {
	if(daemonMap.find(func) != daemonMap.end()) {
		daemonMap[func]->remove();
		delete daemonMap[func];
		daemonMap[func] = nullptr;
	}
}
