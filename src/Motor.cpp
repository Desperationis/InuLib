#include "Motor.h"
#include "BitManip.h"
#include "pros/api_legacy.h"
#include "api.h"

using namespace pros::c;

int16_t reversed_mask = 0;

void motor_set_sign(tMotor port, bool reversed) {
	bit_clear(&reversed_mask, port - 1);

	if(reversed) {
		bit_set(&reversed_mask, port - 1);
	}
}

byte motor_get_sign(tMotor port) {
	return bit_read(&reversed_mask, port - 1) ? -1 : 1;
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
