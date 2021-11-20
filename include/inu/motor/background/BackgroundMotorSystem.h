/** @file BackgroundMotorSystem.h
 * @brief System that updates motors' internal states
 *
 * System that updates all BackgroundMotors.
 */ 

#ifndef BACKGROUNDMOTORSYSTEM_H
#define BACKGROUNDMOTORSYSTEM_H

#include "main.h"
#include <array>
#include "inu/motor/background/BackgroundMotor.h"
#include "inu/Types.hpp"

namespace inu {
	class BackgroundMotorSystem {
	public:

		BackgroundMotorSystem(BackgroundMotorSystem&) = delete;

		void operator=(const BackgroundMotorSystem &) = delete;

		static BackgroundMotorSystem* Instance();

		void SetDelay(unsigned int delay);

		void EnrollMotor(BackgroundMotor* motor);

		void RemoveMotor(BackgroundMotor* motor);

		void RemoveMotor(inu::port port);

		bool MotorExists(inu::port port);

		void BackgroundTask(void* parameters);

	protected:

		BackgroundMotorSystem();

	protected:
		static BackgroundMotorSystem* instance; 
		pros::Task* backgroundTask;
		std::array<BackgroundMotor*, 20> motors;
		unsigned int delay;
	};
}


#endif
