#include <API.h>
#include "Controllers.h"

//enum MOTOR {LEFT = 1, RIGHT, UP, DOWN = 10};
enum MOTOR {BOTTOMLEFT = 1, TOPRIGHT, TOPLEFT, BOTTOMRIGHT = 10};
int motorSign[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

void setMotor(enum MOTOR motor, int speed) {
	motorSet(motor, speed * motorSign[motor - 1]);
}

int motorCap(int value) {
	return value > 127 ? 127 : (value < -127 ? -127 : value);
	
}


void control_xdrive() {

  while(1) {
    /*int delta = joystickGetAnalog(1, 1);
    int y = joystickGetAnalog(1, 3);
    setMotor(LEFT, motorCap(y + delta));
    setMotor(RIGHT, motorCap(-y + delta));

    int x = joystickGetAnalog(1, 4);
    setMotor(UP, motorCap(x + delta));
    setMotor(DOWN, motorCap(-x + delta));*/

    // Everything positive is clockwise
    int x = joystickGetAnalog(1, 4);
    int y = joystickGetAnalog(1, 3);
    int theta = joystickGetAnalog(1, 1);

    setMotor(TOPLEFT, motorCap(y + x + theta));
    setMotor(TOPRIGHT, motorCap(-y + x + theta));
    setMotor(BOTTOMLEFT, motorCap(y - x + theta));
    setMotor(BOTTOMRIGHT, motorCap(-y - x + theta));
    delay(20);
  }
}
