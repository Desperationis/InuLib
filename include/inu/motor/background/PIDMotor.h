/** @file PIDMotor.h
 * @brief Motor data structure used to PID.
 *
 * Motor struct that contains all necessary variables and functions in order to PID. 
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/Motor.hpp"
#include "inu/motor/DoubleVariant.hpp"

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
		 * @returns Whether or not the motor has reached its target (with +-
		 * `error`)
		*/
		bool AtTarget(unsigned int error) const;


		/** 
		 * Use another value, other than the integrated encoder, for use in
		 * comparisions in the PID algorithm. If you want to use the integrated
		 * encoders again simply pass in nullptr. 
		 *
		 * @param foo Pointer to a function that returns the variant as a
		 * double.
		 */ 
		void UseVariant(inu::DoubleVariant* variant);

		void _Update();

	private:
		DoubleVariant* variant;
		inu::Motor motor;

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
