#pragma systemFile
#ifndef SLEW_SOURCE
#define SLEW_SOURCE

typedef struct {
	bool active;
	byte target;
} SlewInfo;

/**
 * Array denoting slewing info, arranged by motor port.
 * Will not work until Slew() is started.
*/
SlewInfo slewMotor[10];

void setSlew(tMotor port, bool active) {
	slewMotor[port].active = active;
}

bool isSlewed(tMotor port) {
	return slewMotor[port].active;
}

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
