/** @file ControllerCallback.h
 * @brief System for adding callbacks to controllers
 *
 * System for adding async and sync callback functions to controller events.
 */

#ifndef CONTROLLERCALLBACK_H
#define CONTROLLERCALLBACK_H

#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include <map>
#include <array>

/**
 * System for adding asynchonous and synchronous callback function to
 * controller events.
*/ 
class ControllerCallback {
private:
	struct CallbackInfo {
		pros::task_fn_t func;
		bool async = false;
		bool buttonPressed = false;
	};

public:
	ControllerCallback(pros::controller_id_e_t id);

	void AsyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

	void SyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

	void PollController();

private:
	pros::Controller controller;
	std::map<pros::controller_digital_e_t, CallbackInfo> callbackButtonMap;

	const std::array<pros::controller_digital_e_t, 12> DIGITAL = {
		pros::E_CONTROLLER_DIGITAL_L1,
		pros::E_CONTROLLER_DIGITAL_L2,
		pros::E_CONTROLLER_DIGITAL_R1,
		pros::E_CONTROLLER_DIGITAL_R2,
		pros::E_CONTROLLER_DIGITAL_UP,
		pros::E_CONTROLLER_DIGITAL_DOWN,
		pros::E_CONTROLLER_DIGITAL_LEFT,
		pros::E_CONTROLLER_DIGITAL_RIGHT,
		pros::E_CONTROLLER_DIGITAL_X,
		pros::E_CONTROLLER_DIGITAL_B,
		pros::E_CONTROLLER_DIGITAL_Y,
		pros::E_CONTROLLER_DIGITAL_A,
	};
};


#endif
