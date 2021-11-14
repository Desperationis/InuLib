/** @file AutoChassis.h
 * @brief Class for moving a chassis autonomously.
 *
 * Abstract class used to move a chassis autonomously.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include <cstdint>
#include "main.h"
#include "inu/motor/PIDProfile.hpp"

namespace inu {
	class AutoChassisBuilder;

	/**
	 * Abstract class used for all future chassis that move autonomously.
	 *
	 * @param builder Pointer to a builder instance to read from.
	*/
	class AutoChassis {
	protected:
		void Copy(const AutoChassis& chassis);

	public:
		AutoChassis(const AutoChassisBuilder* builder);

		AutoChassis(const AutoChassis& chassis);

		virtual ~AutoChassis();

		void operator = (const AutoChassis& chassis) {
			Copy(chassis);
		}

		/** 
		 * Given two speeds x and y, swerve the entire chassis. x and y will be
		 * clamped at the maximum velocity.
		 *
		 * This function will not stall and will simply set the speed of the
		 * motors.
		 *
		 * @param y The speed you want to go forward / backwards.  @param x The
		 * speed at which you want to turn the chassis while turning.
		*/
		virtual void Swerve(std::int8_t y, std::int8_t x) = 0;

		/** 
		 * If a gyro is attached, turns the entire chassis a specific amount of
		 * degrees left or right relative to it's current direction. If no gyro
		 * is attached, do nothing.
		 *
		 * NOTE: There must be no background motor that is currently running on
		 * the same motor ports as what this chassis uses. If there is, this
		 * will do nothing.
		 *
		 * This function has the capability of stalling; If stalling is enabled
		 * then the chassis will timeout and Stop() if the chassis is not able
		 * to face the direction.
		 *
		 * TurnA(90) // Turn 90 degrees clockwise
		 * TurnA(-90) // Turn 90 degrees counterclockwise
		 * TurnA(0); // Don't turn at all
		 *
		 * @param degrees The number of degrees to turn relative to the current
		 * direciton. 
		*/ 
		virtual void TurnA(double degrees) = 0;

		/**
		 * If a gyro is attached, turns the entire chassis to an absolute
		 * heading. If no gyro is attached, do nothing.
		 *
		 * NOTE: There must be no background motor that is currently running on
		 * the same motor ports as what this chassis uses. If there is, this
		 * will do nothing.
		 *
		 * This function has the capability of stalling; If stalling is enabled
		 * then the chassis will timeout if the chassis is not able to face the
		 * direction.
		 *
		 * TurnAbsolute(0) would turn the chassis until it was facing the
		 * direction it was facing since the program started.
		 *
		 * @param degrees The degree to turn at.
		*/ 
		virtual void TurnAbsolute(double degrees) = 0;

		/**
		 * Using the integrated encoders, turn the chassis until all wheels are
		 * within margin of error of `ticks` relative to their current position.
		 *
		 * This function has the capability of stalling; If stalling is enabled
		 * then the chassis will timeout and Stop() if the chassis is not able
		 * to face the direction.
		 *
		 * Turn(1000) would turn until all wheels have a approximate difference
		 * of 1000 relative to their starting position.
		 *
		 * @param ticks The number of encoder ticks to move each wheel. If encoder
		 * units where changed, use the new unit instead.
		*/ 
		virtual void Turn(double ticks) = 0;

		/**
		 * Using the integrated encoders, move the chassis forward until all
		 * wheels are within margin of error of `ticks` relative to their
		 * current position. 
		 *
		 * This function has the capability of stalling; If stalling is enabled
		 * then the chassis will timeout and Stop() if the chassis is not able
		 * to face the direction.
		 *
		 * Forward(1000) would go forward until all wheels have a approximate
		 * difference of 1000 relative to their starting position.
		 *
		 * @param ticks The number of encoder ticks to move each wheel. If
		 * encoder units were changed, use the new unit instead.
		*/ 
		virtual void Forward(double ticks) = 0;

		/**
		 * Shortcut for Forward(-ticks);
		 *
		 * @param ticks The number of encoder ticks to move each wheel. If
		 * encoder units were changed, use the new unit instead.
		 */
		virtual void Backward(double ticks) = 0;

		/**
		 * Completely stop the chassis, even if the wheels are moving in the
		 * background.
		 *
		 * This function should be used for when a condition has been reached
		 * and you need to guarantee that the chassis is completely stationary.
		 */ 
		virtual void Stop() = 0;

		/**
		 * This function only uses encoder readings.
		 *
		 * Stall the chassis until all motors reach their target position plus
		 * or minus a margin of error. If the motors take longer than
		 * `timeout`, then stop stalling.
		 *
		 * @param timeout The value, in seconds, to wait for the motors to
		 * settle.
		*/ 
		virtual void StallUntilSettled(double timeout) = 0;

		/**
		 * This function only uses encoder readings.
		 *
		 * @returns Whether or not all the motors have reached their target
		 * position plus or minus a margin of error.
		*/ 
		virtual bool IsSettled() = 0;

		/**
		 * Tare the encoder value of all motors to 0.
		*/ 
		virtual void TareDistance() = 0;

		/**
		 * Take the absolute value of all motor encoder positions and average
		 * them out.
		 */ 
		virtual double GetDistance() = 0;

	protected:
		unsigned int maxEncoderError;
		unsigned int maxAngleError;
		unsigned int maxVelocity;
		unsigned int currentLimit;
		unsigned int timeoutLimit;
		double timeoutAlignLimit;

		pros::Imu* gyro;
		unsigned int gyroPort;
		bool usesGyro;
		bool isStalling;

		pros::motor_encoder_units_e_t encoderUnits;

		PIDProfile gyroPID;
	};
}


#endif
