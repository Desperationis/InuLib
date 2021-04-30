#include "Slew.h"

ubyte slew_rate = 20;
ubyte slew_delay = 20;
int16_t active_mask = 0;
byte slew_target[10];
TaskHandle slew_handle = NULL;

void slew_set_rate(ubyte rate) {
	slew_rate = rate;
}

void slew_set_delay(ubyte delay) {
	slew_delay = delay;
}

void slew_set_active(tMotor port, bool active) {
	bit_clear(&active_mask, port - 1);

	if(active) {
		bit_set(&active_mask, port - 1);
	}
}

bool slew_get_active(tMotor port) {
	return bit_read(&active_mask, port - 1);
}

void slew_set(tMotor port, int speed) {
	if(slew_get_active(port)){
		slew_target[port - 1] = speed;
	}
	else {
		motor_set(port, speed);
	}
}

/*
	Linearly interpolates between two values via a maximum amount.
*/
short _interpolate(byte original, byte step, byte target){
	short difference = original - target;

	if(abs(difference) > step){
		int sign = difference > 0 ? 1 : (difference < 0 ? -1 : 0);
		return original + (sign * step);
	}

	return target;
}

void _slew_task() {
	while(true) {
		// For each motor, step toward its target if activated.
		for(size_t port = 1; port <= 10; port++) {
			if(slew_get_active(port)) {
				motor_set(port, _interpolate(motor_get(port), slew_rate, slew_target[port - 1]));
			}
		}

		delay(slew_delay);
	}
}

void slew_start() {
	if(slew_handle == NULL) {
		// Initialize internal variables
		for(size_t port = 1; port <= 10; port++) {
			slew_set_active(port, true);
			slew_set(port, 0);
		}

		slew_handle = taskCreate(_slew_task, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT + 1);
	}
}

void slew_stop() {
	if(slew_handle != NULL) {
		if(taskGetState(slew_handle) == TASK_RUNNING) {
			taskDelete(slew_handle);
		}
	}
}
