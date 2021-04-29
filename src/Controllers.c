#include "Controllers.h"

enum XDRIVE_EDGE_PORTS {LEFT = 1, RIGHT, UP, DOWN = 10};
enum XDRIVE_CORNER_PORTS {BOTTOMLEFT = 1, TOPRIGHT, TOPLEFT, BOTTOMRIGHT = 10};

void control_xdrivecorner() {
  while(1) {
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

void control_xdriveedge() {
  while(1) {
		int x = joystickGetAnalog(1, 4);
		int y = joystickGetAnalog(1, 3);
    int delta = joystickGetAnalog(1, 1);
    setMotor(LEFT, motorCap(y + delta));
    setMotor(RIGHT, motorCap(-y + delta));
    setMotor(UP, motorCap(x + delta));
    setMotor(DOWN, motorCap(-x + delta));

    delay(20);
  }
}
