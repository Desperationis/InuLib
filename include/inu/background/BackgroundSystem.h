/** @file BackgroundSystem.h
 * @brief System that updates all background tasks.
 */ 

#ifndef BACKGROUNDSYSTEM_H
#define BACKGROUNDSYSTEM_H

#include "main.h"
#include <array>
#include "inu/background/BackgroundTask.h"
#include "inu/Types.hpp"

namespace inu {
	class BackgroundSystem {
	public:
		BackgroundSystem(BackgroundSystem&) = delete;

		void operator=(const BackgroundSystem &) = delete;

		static BackgroundSystem* Instance();

		void SetDelay(unsigned int delay);

		unsigned int GetDelay();

		void EnrollTask(BackgroundTask* task);

		void RemoveTask(inu::port port);

		void RemoveTask(BackgroundTask* task);

		bool TaskExists(inu::port port);

		bool TaskExists(BackgroundTask* task);

		void BackgroundSystemTask(void* parameters);

	protected:
		BackgroundSystem();

	protected:
		static BackgroundSystem* instance; 
		pros::Task* backgroundTask;
		std::array<BackgroundTask*, 20> tasks;
		unsigned int delay;
	};
}


#endif
