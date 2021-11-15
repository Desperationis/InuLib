/** @file AutoXChassis.h
 * @brief Class for moving a x-drive powered chassis.
 *
 * Chassis used to control a x-drive.
*/


// NOTE: Due to time, this will be a concrete class used for X-drive

#ifndef XCHASSIS_H
#define XCHASSIS_H

#include "main.h"
#include "inu/auto/chassis/AutoChassis.h"
#include "inu/motor/Motor.h"
#include <memory>

namespace inu {
	class AutoXChassisBuilder;
	class PIDInertialMotor;

	/**
	 * Controls a x-drive powered chassis with a topleft, topright, bottomleft, and
	 * bottomright motor.
	*/ 
	class AutoXChassis : public AutoChassis {
	protected:
		void Copy(const AutoXChassis& chassis);

	public:
		/**
		 * topleft, topright, bottomleft, and bottomright are the motor ports of
		 * their respective motors. It is assumed that the motors are mounted such
		 * that, when powered with a positive speed, the entire chassis turns
		 * clockwise.
		*/ 
		AutoXChassis(const inu::AutoXChassisBuilder& builder);

		AutoXChassis(const AutoXChassis& chassis);

		void operator=(const AutoXChassis& chassis);

		~AutoXChassis();

		virtual void Swerve(std::int8_t y, std::int8_t x) override;

		virtual void TurnA(double degrees) override;

		virtual void TurnAbsolute(double degrees) override;

		virtual void Turn(double ticks) override;

		virtual void Forward(double ticks) override;

		virtual void Backward(double ticks) override;

		virtual void StallUntilSettled(double timeout) override;

		virtual bool IsSettled() override;

		virtual void Stop() override;

		virtual void TareDistance() override;

		virtual double GetDistance() override;

		/**
		 * Shortcut for StrafeRight(-ticks).
		 *
		 * @param ticks The number of encoder ticks to move each wheel. If encoder
		 * units where changed, use the new unit instead.
		*/ 
		virtual void StrafeLeft(double ticks);

		/**
		 * Travel straight to the right using the integrated encoders. 
		 *
		 * This function has the capability of stalling; If stalling is enabled
		 * then the chassis will timeout and Stop() if the chassis is not able
		 * to face the direction.
		 *
		 * @param ticks The number of ticks the motors must meet within margin
		 * of error.
		*/
		virtual void StrafeRight(double ticks);

	protected:
		/**
		 * Deallocates the space of any background motors currently running
		 * that are used by the chassis.
		 *
		 * Call this when you need to be extra sure that no background motors
		 * exist.
		*/ 
		void FreeBackgroundMotors();


		/**
		 * Create background motors, assuming they don't exist. If they do exist,
		 * return false.
		 *
		 * @retuns true if the background motors were able to be created, false
		 * if a background motors is already occupying the space.
		*/
		bool CreateBackgroundMotors();

	protected:
		std::shared_ptr<inu::Motor> topleft;
		std::shared_ptr<inu::Motor> topright;
		std::shared_ptr<inu::Motor> bottomleft;
		std::shared_ptr<inu::Motor> bottomright;

		std::unique_ptr<inu::PIDInertialMotor> inertialTopleft;
		std::unique_ptr<inu::PIDInertialMotor> inertialTopright;
		std::unique_ptr<inu::PIDInertialMotor> inertialBottomleft;
		std::unique_ptr<inu::PIDInertialMotor> inertialBottomright;
	};
}


#endif
