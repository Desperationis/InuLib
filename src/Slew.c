#include "Slew.h"

bool slew_task_started = false;

/**
 * Array denoting slewing info, arranged by motor port.
*/
slewInfo_t _slew_ports[10];

void slew_set_slew(tMotor port, bool active) {
	_slew_ports[port].active = active;
}


bool slew_is_slewed(tMotor port) {
	return _slew_ports[port - 1].active && slew_task_started;
}


void slew_set_motor(tMotor port, int speed) {
	if(slew_is_slewed(port - 1)){
		_slew_ports[port - 1].target = speed;
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
	for(size_t port = 0; port < 10; port++) {
		_slew_ports[port].active = true;
		_slew_ports[port].target = 0;
	}

	slew_task_started = true;

	while(true) {
		// For each motor, step toward its target if activated.
		for(size_t port = 0; port < 10; port++) {
			if(slew_is_slewed(port)) {
				motor_set(port + 1, _slew_step(motor_get(port + 1), SLEW_RATE, _slew_ports[port].target));
			}
		}


		delay(20);
	}
}
