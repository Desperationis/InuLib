/** @file ADIMotor.h
 * @brief Extension of pros::ADIMotor class
 *
 * Extension of the pros::ADIMotor class that allows motor reversal.
*/ 

#ifndef INUADIMOTOR_HPP
#define INUADIMOTOR_HPP

#include "main.h"

namespace inu {
	class ADIMotor {
	public:
		/**
		 * @param port Port of the adi motor, 1-8, which each number
		 * corresponding to a letter (with 'A' starting as 1)
		 */ 
		ADIMotor(unsigned int port) : motor(port) { 
			reversed = false;
		}

		/**
		 * Sets the velocity of the motor [-127, 127].
		 *
		 * @param velocity Velocity of the motor.
		*/ 
		void Set(int velocity) {
			motor.set_value(velocity * (reversed ? -1 : 1));
		}

		/**
		 * @param reversed Whether or not this motor is reversed.
		 */ 
		void SetReversed(bool reversed) {
			this->reversed = reversed;
		}

		/**
		 * @returns Whether or not this motor is reversed.
		*/ 
		bool IsReversed() const {
			return reversed;
		}

		/**
		 * @returns The speed of the motor [-127 ,127].
		*/ 
		std::int32_t GetSpeed() const {
			return motor.get_value();
		}

	private:
		pros::ADIMotor motor;
		bool reversed;
	};
}

#endif
