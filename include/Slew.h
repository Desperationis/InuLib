#ifndef SLEW_H
#define SLEW_H

#ifndef SLEW_RATE
	#define SLEW_RATE 5
#endif

#include <API.h>
#include "Motor.h"


// Struct reserved for each motor port
typedef struct {
	bool active;
	char target;
} slewInfo_t;


/**
 * Set whether or not a motor will be slewed; I.e. whether it's motor[] value
 * will be overriden. All motors are slewed by default.
*/
void slew_set_slew(tMotor port, bool active);


/**
 * Returns whether or not a motor is being slewed or not.
*/
bool slew_is_slewed(unsigned char port);


/**
 * Set the slew target of a motor if the port is activated. If not, speed will
 * be set using motor[].
*/
void slew_set_motor(unsigned char port, int speed);


/*
 * Linearly interpolate between two values by a maximum amount.
*/
short _slew_step(short original, short step, short target);

/**
 * Start slewing all motor ports. If not activated by startTask(), slewing will
 * not occur on all motor ports, meaning they won't be able to be controlled by
 * motor[].
*/
void slew_task();


#endif
