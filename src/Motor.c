#include "Motor.h"

int motorSign[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void setMotor(int motor, int speed) {
	motorSet(motor, speed * motorSign[motor - 1]);
}

int motorCap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
}
