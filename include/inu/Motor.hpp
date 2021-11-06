/** @file Motor.h
 * @brief Extension of pros::Motor class
 *
 * A extension of the pros::Motor class aimed towards autonomous.
*/ 

#include "main.h"



namespace inu {
	class Motor : public pros::Motor {

		Motor(unsigned int port) : pros::Motor(port) {

		}

		/**
		 * Whether or not the motor is settled on its target position by a
		 * margin of error defined as target position - error < position <
		 * position + error.
		 */ 
		bool Settled(unsigned int error) {
			double currentPosition = get_position();
			double targetPosition = get_target_position();

			return currentPosition > targetPosition - error &&
				currentPosition < targetPosition + error;
		}
	};
}
