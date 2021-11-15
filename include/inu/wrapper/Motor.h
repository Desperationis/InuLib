/** @file Motor.h
 * @brief Extension of pros::Motor class
 *
 * A extension of the pros::Motor class.
*/ 

#ifndef INUMOTOR_HPP
#define INUMOTOR_HPP

#include "main.h"
#include "pros/motors.h"

namespace inu {
	class Motor {
	public:
		Motor(unsigned int port);

		void Move(std::int32_t voltage) const;

		void MoveRelative(const double position, const std::int32_t velocity) const;

		void MoveAbsolute(const double position, const std::int32_t velocity) const;

		void SetBrakeMode(pros::motor_brake_mode_e_t mode) const;

		void SetCurrentLimit(const std::int32_t limit) const;

		void SetEncoderUnits(pros::motor_encoder_units_e_t units) const;

		void SetReversed(bool reversed) const;

		bool IsReversed() const;

		double GetPosition() const;

		std::uint8_t GetPort() const;

		std::int32_t GetValue() const;

		void TarePosition() const;

		/**
		 * Whether or not the motor is settled on its target position by a
		 * margin of error defined as target position - error < position <
		 * position + error.
		 */ 
		bool IsSettled(unsigned int error) const;


	private:
		pros::Motor motor;
	};
}

#endif
