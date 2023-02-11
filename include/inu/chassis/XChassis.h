/** @file XChassis.h
 * @brief Class for moving a x-drive powered chassis.
 *
 * Chassis used to control a x-drive.
*/

#ifndef INU_XCHASSIS_H
#define INU_XCHASSIS_H

#include "main.h"
#include "inu/wrapper/Motor.h"
#include "inu/motor/MechMotor.hpp"
#include <memory>

namespace inu {
/**
 * Controls a x-drive powered chassis with a topleft, topright, bottomleft, and
 * bottomright motor.
 */
class XChassis {
public:
	/**
	* topleft, topright, bottomleft, and bottomright are the motor ports of
	* their respective motors. It is assumed that the motors are mounted such
	* that, when powered with a positive speed, the entire chassis turns
	* clockwise.
	*/
	XChassis(inu::port tl, inu::port tr, inu::port bl, inu::port br);

	XChassis(const XChassis &chassis);

	void operator=(const XChassis &chassis);

	~XChassis();

	/**
	 * Using built-in encoders, turn the robot a certain amount of encoder ticks.
	 *
	 * @param ticks Encoder ticks to turn
	*/ 
	virtual void Turn(double ticks);

	/**
	 * Using built-in encoders, move the robot forward a certain amount of encoder
	 * ticks
	 *
	 * @param ticks Encoder ticks to move forward
	*/ 
	virtual void Forward(double ticks);

	/**
	 * Using built-in encoders, move the robot backwards a certain amount of encoder
	 * ticks
	 *
	 * @param ticks Encoder ticks to move backwards
	*/ 
	virtual void Backward(double ticks);

	/**
	 * Completely stop all movement of the robot.
	*/ 
	virtual void Stop();

	/**
	 * Resets total distance traveled.
	*/ 
	virtual void TareDistance();

	/**
	 * Get the average distance all motors have traveled.
	 *
	 * @return Average distance in encoder ticks.
	*/ 
	virtual double GetDistance();

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

	/**
	* Given three velocities forward, right, and turn, swerve the entire
	* chassis. Velocities will be clamped at the maximum velocity of the
	* motor.
	*
	* This function will not stall and will simply set the speed of the
	* motors.
	*
	* @param forward Positive values move the car forward, negative backward.
	* @param right Positive values move car to the right, negative to the
	* left.
	* @param turn Positive values results in clockwise motion, negative
	* for anticlockwise.
	*/
	virtual void Swerve(std::int8_t forward, std::int8_t right, std::int8_t turn);

	/**
	* Exactly like Swerve(), but uses raw voltage from [-127, 127] and
	* clamps it from [-127, 127]. Not accurate for Auton at all; Mainly
	* better for driving.
	*
	* @param forward Positive values move the car forward, negative backward.
	* @param right Positive values move car to the right, negative to the
	* left.
	* @param turn Positive values results in clockwise motion, negative
	* for anticlockwise.
	*/
	virtual void RawSwerve(std::int8_t forward, std::int8_t right,
						 std::int8_t turn);

private:
	template<typename T>
	void ChangeEngine() {
		topleft.ChangeEngine<T>();
		topright.ChangeEngine<T>();
		bottomright.ChangeEngine<T>();
		bottomleft.ChangeEngine<T>();
	}

protected:
  inu::MechMotor topleft;
  inu::MechMotor topright;
  inu::MechMotor bottomleft;
  inu::MechMotor bottomright;
};
} // namespace inu

#endif
