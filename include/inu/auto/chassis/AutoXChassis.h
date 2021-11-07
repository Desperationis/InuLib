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

namespace inu {
	/**
	 * Controls a x-drive powered chassis with a topleft, topright, bottomleft, and
	 * bottomright motor.
	*/ 
	class AutoXChassis : public AutoChassis {
	public:
		/**
		 * topleft, topright, bottomleft, and bottomright are the motor ports of
		 * their respective motors. It is assumed that the motors are mounted such
		 * that, when powered with a positive speed, the entire chassis turns
		 * clockwise.
		*/ 
		AutoXChassis(int topleft, int topright, int bottomleft, int bottomright, int gyro);

		virtual void TurnA(double degrees) override;

		virtual void Turn(double ticks) override;

		virtual void Forward(double ticks) override;

		virtual void Backward(double ticks) override;

		virtual bool IsSettled() override;

		virtual void StrafeLeft(double ticks);

		virtual void StrafeRight(double ticks);

	private:
		inu::Motor topleftMotor;
		inu::Motor toprightMotor;
		inu::Motor bottomleftMotor;
		inu::Motor bottomrightMotor;
		pros::Imu gyro;
	};
}


#endif
