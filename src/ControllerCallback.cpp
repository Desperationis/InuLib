#include "ControllerCallback.h"
#include "pros/misc.h"

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
					//Task asyncTask(cInfo.func, nullptr, "");
				}
			}

			cInfo.buttonPressed = controller.get_digital(button);
		}
	}

}
