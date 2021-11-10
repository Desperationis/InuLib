/** @file PIDInertialMotor.h
 * @brief Motor data structure used to PID the inertial's sensors rotation.
 *
 * Motor struct that contains all necessary variables and functions in order to PID 
 * using the inertial sensor's rotation function. 
 */

#ifndef PIDINERTIALMOTOR_H
#define PIDINERTIALMOTOR_H

#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/Motor.hpp"
#include "main.h"

namespace inu {
	/**
	 * Motor struct that contains data members, getters, and setters used to use a
	 * PID system on a motor.
	*/
	class PIDInertialMotor : public BackgroundMotor {
	public:
		PIDInertialMotor(unsigned int motorPort, unsigned int gyro);

		virtual ~PIDInertialMotor();
		
		bool AtTarget(unsigned int error) const;

		void Set(double target);

		void SetPID(PIDProfile pidProfile);

		void SetReversed(bool reversed);

		void SetMaximumVelocity(unsigned int velocity);

		double GetTarget() const;

		const PIDProfile GetPID() const;

		bool IsReversed() const;

		void _Update();

	private:
		unsigned int maxVelocity;
		inu::Motor motor;
		pros::Imu gyro;

		PIDProfile pidProfile;
		double target;
		float proportion;
		float integral;
		float derivative;
		float pastError;
		bool targetSet;
	};

}


#endif
