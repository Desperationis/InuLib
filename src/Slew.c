#pragma systemFile
#ifndef SLEW_SOURCE
#define SLEW_SOURCE

typedef struct {
	bool active;
	byte target;
} SlewInfo;

/**
 * Array denoting slewing info, arranged by motor port.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
SlewInfo slewMotor[10];

void DisableSlew(tMotor port) {
	slewMotor[port].active = false;
}

bool CanSlew(tMotor port) {
	return slewMotor[port].active;
}


void SetSlewMotor(tMotor port, byte speed) {
	if(CanSlew(port)){
		slewMotor[port].target = speed;
	}
	else {
		motor[port] = speed;
	}
}

task Slew() {
	while(true) {
		for(short port = 0; port < 10; port++) {
			if(CanSlew(port)) {
				motor[port] = Step(motor[port], SLEW_STEP, slewMotor[port].target);
			}
		}
		delay(TASK_DELAY);
	}
}

void StartSlewTask() {
	for(short port = 0; port < 10; port++) {
		slewMotor[port].active = true;
		slewMotor[port].target = 0;
	}

	startTask(Slew);
}


#endif
