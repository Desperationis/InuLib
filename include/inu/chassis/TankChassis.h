/** @file TankChassis.h
 * @brief Class for moving a tank-drive chassis.
 *
 * Chassis used to control a tank-drive chassis
*/

#ifndef INU_TANKCHASSIS_H
#define INU_TANKCHASSIS_H

#include "main.h"
#include "inu/wrapper/Motor.h"
#include "inu/motor/MechMotor.hpp"
#include "inu/motor/engines/EncoderEngine.h"
#include <memory>

namespace inu {

class TankChassis {
public:
	/**
	* topleft, topright, bottomleft, and bottomright are the motor ports of
	* their respective motors. It is assumed that the motors are mounted such
	* that, when powered with a positive speed, the entire chassis turns
	* clockwise.
	*/
	TankChassis(inu::port tl, inu::port tr, inu::port bl, inu::port br);

	TankChassis(const TankChassis &chassis);

	void operator=(const TankChassis &chassis);

	~TankChassis();

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
	 * Given two velocities forward and turn, swerve the entire
	 * chassis. Velocities will be clamped at the maximum velocity of the
	 * motor.
	 *
	 * This function will not stall and will simply set the speed of the
	 * motors.
	 *
	 * @param forward Positive values move the car forward, negative
	 * backward.
	 * @param turn Positive values results in clockwise motion, negative
	 * for anticlockwise.
	 */
	virtual void Swerve(int forward, int turn, int maxVelocity);

	/**
	* Exactly like Swerve(), but uses raw voltage from [-127, 127] and
	* clamps it from [-127, 127]. Not accurate for Auton at all; Mainly
	* better for driving.
	*
	* @param forward Positive values move the car forward, negative backward.
	* @param turn Positive values results in clockwise motion, negative
	* for anticlockwise.
	*/
	virtual void RawSwerve(int forward, int turn);

private:
	template<typename T, typename...A>
	void ChangeEngine(A...args) {
		topleft.ChangeEngine<T>(args...);
		topright.ChangeEngine<T>(args...);
		bottomright.ChangeEngine<T>(args...);
		bottomleft.ChangeEngine<T>(args...);
	}

	void Execute();

	/**
	 * When using EncoderEngine, wait for all motors to finish.
	 *
	 * @param steadyWait Seconds to wait after all motors are in "steady
	 * state". This ensures that the motors have even more time to adjust
	 * themselves (slowly) to the desired target.
	 */
	void WaitForEncoders(double steadyWait); 

protected:
	engine::EncoderEngineSettings encoderSettings;
	
	inu::MechMotor topleft;
	inu::MechMotor topright;
	inu::MechMotor bottomleft;
	inu::MechMotor bottomright;
};
} // namespace inu

#endif
