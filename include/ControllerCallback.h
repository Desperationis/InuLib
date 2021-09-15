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

/**
 * System for adding asynchonous and synchronous callback function to
 * controller events.
*/ 
class ControllerCallback {
public:
	ControllerCallback(pros::controller_id_e_t id);

	void AsyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

	void SyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

private:
	pros::Controller controller;
	pros::Task* asyncTask = nullptr;
};


#endif
