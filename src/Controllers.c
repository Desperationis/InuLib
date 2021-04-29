#include "Controllers.h"

enum XDRIVE_EDGE_PORTS {LEFT = 1, RIGHT, UP, DOWN = 10};
enum XDRIVE_CORNER_PORTS {BOTTOMLEFT = 1, TOPRIGHT, TOPLEFT, BOTTOMRIGHT = 10};

void control_xdrivecorner() {
  while(1) {
    int x = joystickGetAnalog(1, 4);
		int y = joystickGetAnalog(1, 3);
    int theta = joystickGetAnalog(1, 1);

    slew_set_motor(TOPLEFT, motorCap(y + x + theta));
    slew_set_motor(TOPRIGHT, motorCap(-y + x + theta));
    slew_set_motor(BOTTOMLEFT, motorCap(y - x + theta));
    slew_set_motor(BOTTOMRIGHT, motorCap(-y - x + theta));
    delay(20);
  }
}

void control_xdriveedge() {
  while(1) {
		int x = joystickGetAnalog(1, 4);
		int y = joystickGetAnalog(1, 3);
    int delta = joystickGetAnalog(1, 1);
    slew_set_motor(LEFT, motorCap(y + delta));
    slew_set_motor(RIGHT, motorCap(-y + delta));
    slew_set_motor(UP, motorCap(x + delta));
    slew_set_motor(DOWN, motorCap(-x + delta));

    delay(20);
  }
}
