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
#include "inu/wrapper/Motor.h"
#include "inu/motor/PID.hpp"
#include "main.h"

namespace inu {
	class PIDInertialMotor : public BackgroundMotor {
	public:
		PIDInertialMotor(unsigned int motorPort, unsigned int gyro, const PIDProfile& profile);

		virtual ~PIDInertialMotor();
		
		bool AtTarget(unsigned int error) const;

		void Set(double target);

		void SetPID(const PIDProfile& pidProfile);

		void SetMaximumVelocity(unsigned int velocity);

		double GetTarget() const;

		const PIDProfile GetPID() const;

		bool IsReversed() const;

		void _Update();

	private:
		inu::Motor motor;
		pros::Imu gyro;
		inu::PID pid;
	};

}


#endif
