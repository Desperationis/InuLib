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
#include "inu/motor/Motor.hpp"
#include "inu/motor/background/PIDInertialMotor.h"


namespace inu {

	class AutoXChassisBuilder;

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
		AutoXChassis(const inu::AutoXChassisBuilder* builder);

		AutoXChassis(const AutoXChassis& chassis);

		void operator=(const AutoXChassis& chassis);

		~AutoXChassis();

		// TODO; Rule of three with destructor here for motors

		virtual void TurnA(double degrees) override;

		virtual void TurnAbsolute(double degrees) override;

		virtual void Turn(double ticks) override;

		virtual void Forward(double ticks) override;

		virtual void Backward(double ticks) override;

		virtual void StallUntilSettled(double timeout) override;

		virtual bool IsSettled() override;

		virtual void Stop() override;

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

	private:
		inu::Motor* topleftMotor;
		inu::Motor* toprightMotor;
		inu::Motor* bottomleftMotor;
		inu::Motor* bottomrightMotor;

		inu::PIDInertialMotor* topleft;
		inu::PIDInertialMotor* topright;
		inu::PIDInertialMotor* bottomleft;
		inu::PIDInertialMotor* bottomright;
	};
}


#endif
