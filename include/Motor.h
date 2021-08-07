/** @file Motor.h
 * @brief Wrapper for motor functions
 *
 * Wrapper for motor functions; Intended to make controlling motors easier.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <API.h>
#include "Types.h"

/**
 * Reverses a motor port; This information is kept in an internal bitmask.
 *
 * @param port Port of the motor.
 * @param reversed Whether or not this motor will be reversed.
*/
void motor_set_sign(tMotor port, bool reversed);

/**
 * Get normalized direction of a motor.
 *
 * @param port Port of the motor.
 * @return -1 if a port is reversed, 1 otherwise.
*/
byte motor_get_sign(tMotor port);

/**
 * Set speed of a motor port. This takes into account motor direction, so a
 * positive value might not always turn the motor clockwise.
 *
 * @see #motor_set_sign(tMotor port, bool reversed)
 * @param port Port of the motor.
 * @param speed Speed of the motor; Can be negative.
*/
void motor_set(tMotor port, byte speed);

/**
 * Get speed of the motor. The speed returned is multiplied by -1 if the motor
 * if reversed.
 *
 * @see #motor_set(tMotor port, byte speed)
 * @param port Port of the motor.
 * @return Speed of the motor.
*/
byte motor_get(tMotor port);

/**
 * Clamp a value to the range accepted by VEX motors.
 *
 * @param Integer you want to clamp.
 * @return Clamped value between [-127, 127], inclusive.
*/
byte motor_cap(int value);

#endif
