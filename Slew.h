#pragma systemFile
#ifndef SLEW_SOURCE
#define SLEW_SOURCE

#include "Helpers.h"

/**
 * Blacklist of motors to not be slewed. Organized by motor
 * port, any ports set to true will not be slewed.
*/
bool slewBlacklist[10];

/**
 * Array denoting motor speed, arranged by motor port.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
short slewMotor[10];


/**
 * Permanently disable a motor from being able to slew.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
void DisableSlew(tMotor port) {
	slewBlacklist[port] = true;
}


/**
 * Determine if a motor is slewed or not.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
bool CanSlew(tMotor port) {
	return !slewBlacklist[port];
}


/**
 * Set the slew target of a motor, if possible. If not,
 * speed will be set using motor[].
*/
void SetSlewMotor(tMotor port, byte speed) {
	if(CanSlew(port)){
		slewMotor[port] = speed;
	}
	else {
		motor[port] = speed;
	}
}


/**
 * The background task responsible for slewing motors.
 * It is recommended to start this with StartSlewTask().
*/
task Slew() {
	while(true) {
		for(short port = 0; port < 10; port++) {
			if(CanSlew(port)) {
				motor[port] = Step(motor[port], SLEW_STEP, slewMotor[port]);
			}
		}
		delay(TASK_DELAY);
	}
}


/**
 * @setup
 *
 * Starts up the Slew() task and resets internal variables. By default,
 * motors are slewed. This can be changed using DisableSlew(port).
*/
void StartSlewTask() {
	for(short port = 0; port < 10; port++) {
		slewMotor[port] = 0;
		slewBlacklist[port] = false;
	}

	startTask(Slew);
}


#endif
