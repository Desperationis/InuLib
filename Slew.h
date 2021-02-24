#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

#ifndef SLEW_STEP
	// The maximum amount of motor speed difference per tick.
	// Lower values are better.
	#define SLEW_STEP 15
#endif

typedef struct {
	bool active;
	byte target;
} SlewInfo;

/**
 * Array denoting slewing info, arranged by motor port.
 * Will not work until Slew() is started.
*/
SlewInfo slewMotor[10];

/**
 * Set whether or not a motor will be slewed by setSlewMotor();
 * All motors are slewed by default.
 * Will not work until Slew() is started.
*/
void setSlew(tMotor port, bool active) {
	slewMotor[port].active = active;
}


/**
 * Whether or not a motor is being slewed or not.
 * Will not work until Slew() is started.
*/
bool isSlewed(tMotor port) {
	return slewMotor[port].active;
}


/**
 * Set the slew target of a motor if the port is activated. If not,
 * speed will be set using motor[].
 * Will not work until Slew() is started.
*/
void setSlewMotor(tMotor port, byte speed) {
	if(isSlewed(port)){
		slewMotor[port].target = speed;
	}
	else {
		motor[port] = speed;
	}
}

/**
 * Linearly interpolates between two values by a
 * maximum amount.
*/
short Step(short original, short step, short target){
	if(abs(original - target) > step){
		return original + (sgn(target - original) * step);
	}
	return target;
}

/**
 * Starts slewing all motor ports. If not deactivated by setSlewMotor(),
 * every single motor port in motor[] will, by default, not be able to be controlled through
 * the array, but only by setSlewMotor().
*/
task Slew() {
	for(short port = 0; port < 10; port++) {
		slewMotor[port].active = true;
		slewMotor[port].target = 0;
	}

	while(true) {
		for(short port = 0; port < 10; port++) {
			if(isSlewed(port)) {
				// For each motor, step toward its target
				motor[port] = Step(motor[port], SLEW_STEP, slewMotor[port].target);
			}
		}
		delay(TASK_DELAY);
	}
}

#endif
