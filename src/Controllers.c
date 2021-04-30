#include "Controllers.h"

enum XDRIVE_EDGE_PORTS {LEFT = 1, RIGHT, UP, DOWN = 10};
enum XDRIVE_CORNER_PORTS {BOTTOMLEFT = 1, TOPRIGHT, TOPLEFT, BOTTOMRIGHT = 10};

void control_xdrivecorner() {
  while(1) {
    int x = joystickGetAnalog(1, 4);
		int y = joystickGetAnalog(1, 3);
    int theta = joystickGetAnalog(1, 1);

    slew_set_motor(TOPLEFT, motor_cap(y + x + theta));
    slew_set_motor(TOPRIGHT, motor_cap(-y + x + theta));
    slew_set_motor(BOTTOMLEFT, motor_cap(y - x + theta));
    slew_set_motor(BOTTOMRIGHT, motor_cap(-y - x + theta));
    delay(20);
  }
}

void control_xdrivecorner_gamer() {
  while(1) {
		int y = joystickGetAnalog(1, 3);
    int theta = joystickGetAnalog(1, 1);

    slew_set_motor(TOPLEFT, motor_cap(y + theta));
    slew_set_motor(TOPRIGHT, motor_cap(-y + theta));
    slew_set_motor(BOTTOMLEFT, motor_cap(y + theta));
    slew_set_motor(BOTTOMRIGHT, motor_cap(-y + theta));
    delay(20);
  }
}

void control_xdriveedge() {
  while(1) {
		int x = joystickGetAnalog(1, 4);
		int y = joystickGetAnalog(1, 3);
    int delta = joystickGetAnalog(1, 1);
    slew_set_motor(LEFT, motor_cap(y + delta));
    slew_set_motor(RIGHT, motor_cap(-y + delta));
    slew_set_motor(UP, motor_cap(x + delta));
    slew_set_motor(DOWN, motor_cap(-x + delta));

    delay(20);
  }
}
