/** @file PIDMotor.h
 * @brief Motor data structure used to PID with integrated encoders.
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/wrapper/Motor.h"
#include "inu/motor/PID.h"

namespace inu {
	class PIDMotor : public BackgroundMotor {
	public:
		PIDMotor(unsigned int port, const PIDProfile& profile);

		virtual ~PIDMotor();

		/**
		 * Sets a target encoder value to PID towards.
		 *
		 * @param target Target encoder value.
		*/ 
		void Set(int target);

		/**
		 * @param profile The PIDProfile of this motor.
		 */
		void SetPID(const PIDProfile& profile);

		/**
		 * @returns The target encoder value for this motor.
		*/ 
		int GetTarget() const;

		/**
		 * @returns Whether or not the motor has reached its target (with +-
		 * `error`)
		*/
		bool AtTarget(unsigned int error) const;

		/**
		 * Set the maximum velocity possible [0 - 127] that this motor is
		 * allowed to go to.
		 *
		 * @param velocity The max velocity of the motor.
		 */
		void SetMaximumVelocity(unsigned int velocity);

		void _Update();

	private:
		inu::PID pid;
		inu::Motor motor;
	};

}


#endif
