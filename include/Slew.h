#ifndef SLEW_H
#define SLEW_H

#include <API.h>
#include "Motor.h"
#include "BitManip.h"

/*
	Start background slew task if not started. Once started, the speeds of ALL
	motors will be overriden and be set to 0, meaning motor_set and motorSet
	won't have an effect on motor speed unless deactivated by slew_set_active.
	In addition to this, any motors that were configured using slew_set_active
	and slew_set will have no effect if they were called before this function.
*/
void slew_start();

/*
	Set the maximum motor speed change (default: 20) per tick (default: ~20ms).
	Lower values increase the amount of time for motors to ramp up or down to
	target speed, and higher values decrease it.
*/
void slew_set_rate(ubyte rate);

/*
	Set the time in milliseconds the background slew task needs to wait until it
	updates (default: 20ms). It is not recommended to mess around with this
	unless you know what you're doing, as motors themselves update every 20ms.
*/
void slew_set_delay(ubyte delay);

/*
	Whether or not the slew task is running.
*/
bool slew_is_running();

/*
 	Stop background slew task, if running.
*/
void slew_stop();

/*
 	Set whether or not a motor will be slewed. All motors are slewed by default.
	If a motor is activated, motor_set and motorSet will have no effect.
*/
void slew_set_active(tMotor port, bool active);

/*
 	Whether or not a motor is controlled by the background slew task.
*/
bool slew_get_active(unsigned char port);

/*
	Set the slew target of a motor if the port is activated. If not, speed will
 	be set using motor_set / motorSet.
*/
void slew_set(unsigned char port, int speed);

#endif
