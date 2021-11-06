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
#include "pros/rtos.h"
#include <map>
#include <array>


namespace inu {
	/**
	 * System for adding asynchonous and synchronous callback function to
	 * controller events.
	*/ 
	class ControllerCallback {
	private:
		/**
		 * Contains information and data about a callback.
		*/ 
		struct CallbackInfo {
			pros::task_fn_t func;
			bool async = false;
			bool buttonPressed = false;
		};

	public:
		/**
		 * @param id PROS ID of the controller you want to add callbacks to.
		*/ 
		ControllerCallback(pros::controller_id_e_t id);

		/**
		 * Adds a asynchronous callback to a button that will run in the
		 * background. Background task can be accessed by GetTask(). Task will not
		 * get started in the background twice even if you press the button
		 * multiple times.
		 *
		 * @param button Button that you want to assign the callback to.
		 * @param func Callback function you want run.
		*/ 
		void AsyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

		/**
		 * Adds a synchronous callback to a button that will halt the program until it is 
		 * done executing.
		 *
		 * @param button Button that you want to assign the callback to.
		 * @param func Callback function you want to run.
		*/ 
		void SyncCallback(pros::controller_digital_e_t button, pros::task_fn_t func);

		/**
		 * Check the controller to see if any buttons have been pressed and
		 * activate callbacks accordingly. If the callback is asynchronous, this
		 * will check if the task is already running before starting a new one.
		*/ 
		void PollController();

		/**
		 * Get a pointer to the pros::Task* object that is running asynchronous
		 * `func`. If the task is suspended, not running, or doesn't exist, this
		 * will return nullptr.
		 *
		 * @param func Callback function to search with.
		*/ 
		pros::Task* GetTask(pros::task_fn_t func);

		/**
		 * If it exists, deallocate the memory of a task that is associated with a
		 * certain async callback. If it doesn't exist, do nothing.
		 *
		 * @param func Callback function to search with.
		*/ 
		void DeleteTask(pros::task_fn_t func);

	private:
		pros::Controller controller;
		std::map<pros::controller_digital_e_t, CallbackInfo> callbackButtonMap;
		std::map<pros::task_fn_t, pros::Task*> daemonMap;

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

}

#endif
