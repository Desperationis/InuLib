/** @file AutoChassis.h
 * @brief Class for moving a chassis autonomously.
 *
 * Abstract class used to move a chassis autonomously.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include <cstdint>
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "pros/imu.hpp"

namespace inu {
	/**
	 * Abstract class used for all future chassis that move autonomously.
	*/
	class AutoChassis {
	public:
		AutoChassis(const AutoChassisBuilder* builder) {
			maxAngleError = builder->GetMaxAngleError();
			maxEncoderError = builder->GetMaxEncoderError();
			maxVelocity = builder->GetMaxVelocity();
			currentLimit = builder->GetCurrentLimit();
			timeoutLimit = builder->GetTimeout();

			usesGyro = builder->UsesGyro();
			gyro = nullptr;

			if(usesGyro) {
				gyro = new pros::Imu(builder->GetGyro());
				gyroPID = builder->GetGyroPID();
			}

			encoderUnits = builder->GetEncoderUnits();
		}


		virtual void TurnA(double degrees) = 0;

		virtual void Turn(double ticks) = 0;

		virtual void Forward(double ticks) = 0;

		virtual void Backward(double ticks) = 0;

		virtual void StallUntilSettled(double timeout) = 0;

		virtual bool IsSettled() = 0;

	protected:
		unsigned int maxEncoderError;
		unsigned int maxAngleError;
		unsigned int maxVelocity;
		unsigned int currentLimit;
		unsigned int timeoutLimit;

		pros::Imu* gyro;
		bool usesGyro;

		pros::motor_encoder_units_e_t encoderUnits;

		PIDProfile gyroPID;
	};
}


#endif
