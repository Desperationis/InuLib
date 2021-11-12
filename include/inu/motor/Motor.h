/** @file Motor.h
 * @brief Extension of pros::Motor class
 *
 * A extension of the pros::Motor class.
*/ 

#ifndef INUMOTOR_HPP
#define INUMOTOR_HPP

#include "main.h"

namespace inu {
	class Motor : public pros::Motor {
	public:
		Motor(unsigned int port);

		/**
		 * Whether or not the motor is settled on its target position by a
		 * margin of error defined as target position - error < position <
		 * position + error.
		 */ 
		bool IsSettled(unsigned int error) const;

		/**
		 * Returns a clone of this motor; You are responsible for managing the
		 * memory.
		 *
		 * @returns a clone of this motor.
		*/ 
		Motor* Clone() const;
	};
}

#endif
