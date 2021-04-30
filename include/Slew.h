#ifndef SLEW_H
#define SLEW_H

#ifndef SLEW_RATE
	#define SLEW_RATE 5
#endif

#include <API.h>
#include "Motor.h"
#include "BitManip.h"


/*
 	Starts slewing all motors (taking into account if the motors are reversed),
	if not started already. This overrides both motor_set and setMotor with
	slew_set unless slew is deactivated on those ports. In addition to this,
	starting this task clears all the settings that were configured before it, so
	be sure to activate and use motors after starting this task.
*/
void slew_start();

/*
	Sets the maximum motor speed change per tick; The "slew". Lower values
	increase slew, and higher values decrease it. By default, this is set to 20.
*/
void slew_set_rate(ubyte rate);

/*
	Sets the delay of the slew task; By default, this is set to 20. Big delays
	increase slew, and lower values decreases slew.
*/
void slew_set_delay(ubyte delay);

/*
	Whether or not the slew task is running.
*/
bool slew_is_running();

/*
 	Stops the task for slewing if it's currently running.
*/
void slew_stop();

/*
 	Set whether or not a motor will be slewed; I.e. whether it's motor[] value
 	will be overriden by slew_set. All motors are slewed by default.
*/
void slew_set_active(tMotor port, bool active);

/*
 	Returns whether or not a motor is being slewed or not.
*/
bool slew_get_active(unsigned char port);

/*
	Set the slew target of a motor if the port is activated. If not, speed will
 	be set using motor_set.
*/
void slew_set(unsigned char port, int speed);

#endif
