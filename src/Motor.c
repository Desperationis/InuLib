#include "Motor.h"

int motorSign[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void setMotorSign(int port, bool reversed) {
	motorSign[port - 1] = reversed ? -1 : 1;
}

void setMotor(int port, int speed) {
	motorSet(port, speed * motorSign[port - 1]);
}

int getMotor(int port) {
	return motorGet(port) * motorSign[port - 1];
}

int motorCap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
}
