#include "Motor.h"

int16_t motorSign = 0;

void motor_set_sign(tMotor port, bool reversed) {
	motorSign &= ~(1 << (port - 1));

	if(reversed) {
		motorSign += (1 << (port - 1));
	}
}

byte motor_get_sign(tMotor port) {
	return motorSign >> (port - 1) == 1 ? -1 : 1;
}

void motor_set(tMotor port, byte speed) {
	motorSet(port, speed * motor_get_sign(port));
}

byte motor_get(tMotor port) {
	return motorGet(port) * motor_get_sign(port);
}

byte motor_cap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
}
