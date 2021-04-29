#include <API.h>
#include "Motor.h"

int16_t motorSign = 0;

void setMotorSign(int port, bool reversed) {
	motorSign &= ~(1 << (port - 1));

	if(reversed) {
		motorSign += (1 << (port - 1));
	}
}

int getSign(int port) {
	return motorSign >> (port - 1) == 1 ? -1 : 1;
}

void setMotor(int port, int speed) {
	motorSet(port, speed * getSign(port));
}

int getMotor(int port) {
	return motorGet(port) * getSign(port);
}

int motorCap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
}
