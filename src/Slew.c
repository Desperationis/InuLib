#include "Slew.h"

bool slew_task_started = false;

/**
 * Array denoting slewing info, arranged by motor port.
*/
slewInfo_t slew_ports[10];


slewInfo_t* slew_get_port(tMotor port) {
	if(port <= 10 && port > 0) {
		return &slew_ports[port - 1];
	}
	return NULL;
}


void slew_set_slew(tMotor port, bool active) {
	slew_get_port(port)->active = active;
}


bool slew_is_slewed(tMotor port) {
	return slew_get_port(port)->active && slew_task_started;
}


void slew_set_motor(tMotor port, int speed) {
	if(slew_is_slewed(port)){
		slew_get_port(port)->target = speed;
	}
	else {
		motor_set(port, speed);
	}
}

int signal(int value) {
  return value > 0 ? 1 : (value < 0 ? -1 : 0);
}


short _slew_step(short original, short step, short target){
	if(abs(original - target) > step){
		return original + (signal(target - original) * step);
	}
	return target;
}

void slew_task() {
	// Initialize internal variables
	for(size_t port = 1; port <= 10; port++) {
		slew_get_port(port)->active = true;
		slew_get_port(port)->target = 0;
	}

	slew_task_started = true;

	while(true) {
		// For each motor, step toward its target if activated.
		for(size_t port = 1; port <= 10; port++) {
			if(slew_is_slewed(port)) {
				motor_set(port, _slew_step(motor_get(port), SLEW_RATE, slew_get_port(port)->target));
			}
		}

		delay(20);
	}
}
