/** @file AutoChassisBuilder.h
 * @brief Base class for AutoChassis builders
 *
 * Base class for AutoChassisBuilders
*/ 

#ifndef AUTOCHASSISBUILDER_H
#define AUTOCHASSISBUILDER_H

#include "inu/motor/PIDProfile.hpp"
#include "pros/motors.h"

namespace inu {
	class AutoChassisBuilder {
	public:
		AutoChassisBuilder() {
			maxEncoderError = 10;
			maxAngleError = 5;
			maxVelocity = 127;
			currentLimit = 2000;
			usesGyro = false;

			encoderUnits = pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_COUNTS;
		};

		void SetMaxEncoderError(unsigned int error) {
			maxEncoderError = error;
		}

		void SetMaxVelocity(unsigned int velocity) {
			maxVelocity = velocity;
		}

		void SetMaxAngleError(unsigned int error) {
			maxAngleError = error;
		}

		void SetCurrentLimit(unsigned int limit) {
			currentLimit = limit;
		}

		void SetGyro(unsigned int port) {
			usesGyro = true;
			gyro = port;
		}

		void SetEncoderUnits(pros::motor_encoder_units_e_t units) {
			encoderUnits = units;
		}

		void SetGyroPID(PIDProfile profile) {
			gyroPID = profile;
		}

		unsigned int GetMaxEncoderError() const {
			return maxEncoderError;
		}

		unsigned int GetMaxVelocity() const {
			return maxVelocity;
		}

		unsigned int GetMaxAngleError() const {
			return maxAngleError;
		}

		unsigned int GetCurrentLimit() const {
			return currentLimit;
		}

		unsigned int GetGyro() const {
			return gyro;
		}

		pros::motor_encoder_units_e_t GetEncoderUnits() const {
			return encoderUnits;
		}

		bool UsesGyro() const {
			return usesGyro;
		}

		PIDProfile GetGyroPID() const {
			return gyroPID;
		}

	private:
		unsigned int maxEncoderError;
		unsigned int maxAngleError;
		unsigned int maxVelocity;
		unsigned int gyro;
		unsigned int currentLimit;

		bool usesGyro;

		pros::motor_encoder_units_e_t encoderUnits;

		PIDProfile gyroPID;
	};
}


#endif
