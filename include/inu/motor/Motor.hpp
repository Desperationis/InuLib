/** @file Motor.h
 * @brief Extension of pros::Motor class
 *
 * A extension of the pros::Motor class.
*/ 

#include "main.h"

#ifndef INUMOTOR_HPP
#define INUMOTOR_HPP

namespace inu {
	class Motor : public pros::Motor {
	public:

		Motor(unsigned int port) : pros::Motor(port) {

		}

		/**
		 * Whether or not the motor is settled on its target position by a
		 * margin of error defined as target position - error < position <
		 * position + error.
		 */ 
		bool IsSettled(unsigned int error) const {
			double currentPosition = get_position();
			double targetPosition = get_target_position();

			return currentPosition > targetPosition - error &&
				currentPosition < targetPosition + error;
		}

		Motor* Clone() {
			// Test this to see if it is a full copy
			return new Motor(*this);
		}
	};
}

#endif
