/** @file Motor.h
 * @brief Extension of pros::Motor class
 *
 * A extension of the pros::Motor class.
*/ 

#ifndef INUMOTOR_HPP
#define INUMOTOR_HPP

#include "main.h"
#include "inu/Types.hpp"

namespace inu {
	class Motor {
	public:
		/**
		 * @param port Port of the motor, 1-20.
		*/ 
		Motor(inu::port port);

		/**
		 *	Sets the voltage of the motor using joystick ranges; Brake mode
		 *	will not work.
		 *
		 * @param voltage Voltage of the motor, [-127, 127]. Value will be
		 * clamped.
		*/ 
		void Move(int voltage) const;

		/**
		 * Using the integrated control loop, move to a specific position
		 * relative to the current position.
		 *
		 * @param position Target position from current position.
		 * @param velocity Max velocity from +-100, 200, or 600.
		*/ 
		void MoveRelative(const double position, int velocity) const;

		/**
		 * Using the integrated control loop, move to a specific position
		 * absolute to whenever TarePosition() was called.
		 *
		 * @param position Target absolute position.
		 * @param velocity Max velocity from +-100, 200, or 600.
		*/ 
		void MoveAbsolute(const double position, int velocity) const;

		/**
		 * Moves the motor at a constant velocity using the integrated
		 * control loop.
		 *
		 * @param velocity Velocity from +-100, 200, or 600.
		*/ 
		void MoveVelocity(int velocity) const;

		/**
		 * Set the brake mode used by MoveVelocity().
		 *
		 * @param mode The brake mode.
		*/ 
		void SetBrakeMode(pros::motor_brake_mode_e_t mode) const;

		/**
		 * Set the current limit of the motor.
		 *
		 * @param limit Current limit.
		*/ 
		void SetCurrentLimit(const int limit) const;

		/**
		 * Change the encoder units of the motor.
		 *
		 * @param units The new units
		*/ 
		void SetEncoderUnits(pros::motor_encoder_units_e_t units) const;

		/**
		 * Sets whether or not a motor is reversed.
		 *
		 * @param reverse Whether or not the motor will be reversed.
		*/ 
		void SetReversed(bool reverse) const;

		/**
		 * @returns Whether or not the motor is reversed.
		*/ 
		bool IsReversed() const;

		/**
		 * @returns The current position of the motor with the desired encoder
		 * units.
		*/ 
		double GetPosition() const;

		/**
		 * @returns The target position of the motor with the desired encoder
		 * units.
		*/ 
		double GetTargetPosition() const;

		/**
		 * @returns The port of the motor.
		*/ 
		inu::port GetPort() const;

		/**
		 * @returns the voltage of the motor [-127, 127]
		*/ 
		int GetVoltage() const;

		/**
		 * @returns the actual velocity of the motor.
		*/ 
		int GetActualVelocity() const;

		/**
		 * @returns the target velocity of the motor.
		*/ 
		int GetTargetVelocity() const;

		/**
		 * Tare the position of the encoder.
		*/ 
		void TarePosition();

		/**
		 * Whether or not the motor is settled on its target position by a
		 * margin of error defined as target position - error < position <
		 * position + error.
		 */ 
		bool IsSettled(int error) const;

	private:
		/**
		 * Caps voltage at [-127, 127].
		*/ 
		int CapVoltage(int velocity) const;

		/**
		 * Caps velocity at +- 100, 200, or 600 depending on gearing.
		*/ 
		int CapVelocity(int velocity) const;

	private:
		pros::Motor motor;
		int tare;
	};
}

#endif
