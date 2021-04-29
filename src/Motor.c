#include <API.h>
#include "Motor.h"

int16_t motorSign = 0;

void motor_set_sign(int port, bool reversed) {
	motorSign &= ~(1 << (port - 1));

	if(reversed) {
		motorSign += (1 << (port - 1));
	}
}

int motor_get_sign(int port) {
	return motorSign >> (port - 1) == 1 ? -1 : 1;
}

void motor_set(int port, int speed) {
	motorSet(port, speed * motor_get_sign(port));
}

int motor_get(int port) {
	return motorGet(port) * motor_get_sign(port);
}

int motor_cap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
}
