/** #file BackgroundTask.h
 * @brief Abstract class for background tasks on a specific port.
 *
 * Abstract class for anything that needs to be constantly updated in the 
 * background relating to a single port, whether it be LED lights or motors.
*/

#ifndef BACKGROUNDTASK_H
#define BACKGROUNDTASK_H

#include "inu/Types.hpp"

namespace inu {

	class BackgroundTask {
	public:
		BackgroundTask() = delete;

		virtual ~BackgroundTask() = default;

		/**
		 * Creates a background task.
		 *
		 * @param port The port that this task uses; Used to keep track of it.
		*/ 
		BackgroundTask(inu::port port) {
			this->port = port;
		}

		/**
		 * Updates the task; This is where your code should go.
		*/ 
		virtual void _Update() = 0;


		/**
		 * @returns The port this task uses.
		*/ 
		virtual inu::port GetPort() const {
			return port;
		}

	protected:
		inu::port port;
	};

}

#endif
