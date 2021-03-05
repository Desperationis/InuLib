#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

#ifndef SLEW_STEP
	#define SLEW_STEP 15 // The maximum amount of motor speed difference per tick.
#endif

#ifndef TASK_DELAY
	#define TASK_DELAY 20
#endif


// Struct reserved for each motor port
typedef struct {
	bool active;
	byte target;
} slewInfo_t;


/**
 * Array denoting slewing info, arranged by motor port.
*/
slewInfo_t _slew_ports[10];


/**
 * Set whether or not a motor will be slewed; I.e. whether it's motor[] value
 * will be overriden. All motors are slewed by default.
*/
void slew_set_slew(tMotor port, bool active) {
	_slew_ports[port].active = active;
}


/**
 * Returns whether or not a motor is being slewed or not.
*/
bool slew_is_slewed(tMotor port) {
	return _slew_ports[port].active;
}


/**
 * Set the slew target of a motor if the port is activated. If not, speed will
 * be set using motor[].
*/
void slew_set_motor(tMotor port, byte speed) {
	if(slew_is_slewed(port)){
		_slew_ports[port].target = speed;
	}
	else {
		motor[port] = speed;
	}
}


/*
 * Linearly interpolate between two values by a maximum amount.
*/
short _slew_step(short original, short step, short target){
	if(abs(original - target) > step){
		return original + (sgn(target - original) * step);
	}
	return target;
}


/**
 * Start slewing all motor ports. If not activated by startTask(), slewing will
 * not occur on all motor ports, meaning they won't be able to be controlled by
 * motor[].
*/
task slew_task() {
	// Initialize internal variables
	for(short port = 0; port < 10; port++) {
		_slew_ports[port].active = true;
		_slew_ports[port].target = 0;
	}

	while(true) {
		// For each motor, step toward its target if activated.
		for(short port = 0; port < 10; port++) {
			if(slew_is_slewed(port)) {
				motor[port] = _slew_step(motor[port], SLEW_STEP, _slew_ports[port].target);
			}
		}

		delay(TASK_DELAY);
	}
}

#endif
