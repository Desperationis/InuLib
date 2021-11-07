/** @file PIDMotor.h
 * @brief Motor data structure used to PID.
 *
 * Motor struct that contains all necessary variables and functions in order to PID. 
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "main.h"
#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"

namespace inu {
	/**
	 * Motor struct that contains data members, getters, and setters used to use a
	 * PID system on a motor.
	*/
	class PIDMotor : public BackgroundMotor {
	public:
		PIDMotor(unsigned int port);

		virtual ~PIDMotor();

		/**
		 * Sets a target encoder value to PID towards.
		 *
		 * @param target Target encoder value.
		*/ 
		void Set(int target);

		/**
		 * Set the PIDProfile that this motor will use.
		 *
		 * @param PIDProfile Constant copy of a PIDProfile.
		*/ 
		void SetPID(PIDProfile pidProfile);

		/**
		 * @returns The target encoder value for this motor.
		*/ 
		int GetTarget() const;

		/**
		 * @returns A copy of the PIDProfile currently in use.
		*/ 
		const PIDProfile GetPID() const;

		/**
		 * @returns Whether or not the motor has reached its target (with +- `error`)
		*/
		bool AtTarget(unsigned int error) const;

		void _Update();

	private:
		PIDProfile pidProfile;
		int target;
		float proportion;
		float integral;
		float derivative;
		float pastError;
		bool targetSet;
	};

}


#endif
