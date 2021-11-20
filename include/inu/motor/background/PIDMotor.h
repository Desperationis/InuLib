/** @file PIDMotor.h
 * @brief Motor data structure used to PID with integrated encoders.
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/wrapper/Motor.h"
#include "inu/motor/PID.hpp"
#include "inu/Types.hpp"
#include "pros/motors.h"

namespace inu {
	class PIDMotor : public BackgroundMotor {
	public:
		PIDMotor(inu::port port, const PIDProfile& profile);

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
		bool AtTarget(int error) const;

		/**
		 * Set the maximum velocity possible that this motor is allowed to go
		 * to. Max velocity will be capped by motor gearing if it's too high.
		 *
		 * @param velocity The max velocity of the motor.
		 */
		void SetMaximumVelocity(int velocity);

		/**
		 * Set the brake mode of the motor.
		 *
		 * @param mode Brake mode.
		*/ 
		void SetBrakeMode(pros::motor_brake_mode_e_t mode);

		/**
		 * @returns the current position of the motor.
		*/ 
		double GetPosition() const;

		void _Update();

	private:
		inu::PID pid;
		inu::Motor motor;
	};

}


#endif
