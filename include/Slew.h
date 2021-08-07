/** @file Slew.h
 * @brief Provides functions for slewing motors.
 *
 * Provides functions for slewing motors. Warning: if you initialize this
 * module, you cannot use Motor.h to control motors unless you disable the
 * slewing for it manually.
 */

#ifndef SLEW_H
#define SLEW_H

#include <API.h>
#include "Motor.h"
#include "BitManip.h"

/**
 * Start background slew task if not started. Once started, the speeds of ALL
 * motors will be overriden and be set to 0, meaning motor_set and motorSet
 * won't have an effect on motor speed unless deactivated by slew_set_active.
 * In addition to this, any motors that were configured using slew_set_active
 * and slew_set will have no effect if they were called before this function.
*/
void slew_start();

/**
 * Set the maximum motor speed change per delay.  Lower values increase the
 * amount of time for motors to ramp up or down to target speed, and higher
 * values decrease it.
 *
 * @param rate Unsigned byte representing maximum amount of change in a slewed
 * motor per delay.
*/
void slew_set_rate(ubyte rate);

/**
 * Set the delay the background slew task needs to wait until it updates. It is
 * not recommended to mess around with this unless you know what you're doing,
 * as motors themselves update every 20ms.
 *
 * @param delay Time, in milliseconds, the background slew task will be delayed
 * by.
*/
void slew_set_delay(ubyte delay);

/**
 * @return True if the slew task is running.
*/
bool slew_is_running();

/**
 * Stop background slew task, if running.
*/
void slew_stop();

/**
 * Set whether or not a motor will be slewed. All motors are slewed by default.
 * If a motor is activated, motor_set and motorSet will have no effect.
 *
 * @see #slew_get_active(tMotor port)
 * @param port Port of the motor you want to toggle.
 * @param active Whether or not this motor will be slewed.
*/
void slew_set_active(tMotor port, bool active);

/**
 * Whether or not a motor is controlled by the background slew task.
 *
 * @see #slew_set_active
 * @param port Port of the motor you want to check.
 * @return True if the motor is slewed.
*/
bool slew_get_active(tMotor port);

/**
 * Set the slew target of a motor if the port is activated. If not, speed will
 * be set using motor_set / motorSet.
 *
 * @param Port of the motor you want to set.
 * @param speed Speed of the motor you want to slew to.
*/
void slew_set(tMotor port, byte speed);

#endif
