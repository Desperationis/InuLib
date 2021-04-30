#include "Controllers.h"

/*
  Task handle to the current_controller; This is automatically managered
  internally in here.
*/
TaskHandle current_controller = NULL;
ubyte control_delay = 20;
float control_scale = 1.0;


void control_set_delay(ubyte delay) {
  control_delay = delay;
}

void control_set_scale(float scale) {
  control_scale = scale;
}

/*
  Sets the speed of a motor controlled by a controller; This tries to take
  advantage of slewing and scales the input
*/
void _control_set_motor(tMotor port, int speed) {
  slew_set(port, motor_cap(speed * control_scale));
}

void control_stop() {
  if(current_controller != NULL) {
    if(taskGetState(current_controller) == TASK_RUNNING) {
      taskDelete(current_controller);
      current_controller = NULL;
    }
  }
}

void control_switch(void(*task_code)(void)) {
  control_stop();
  current_controller = taskRunLoop(task_code, control_scale);
}

void control_xdrivecorner() {
  int x = joystickGetAnalog(1, 4);
	int y = joystickGetAnalog(1, 3);
  int theta = joystickGetAnalog(1, 1);

  _control_set_motor(XDC_TOPLEFT, y + x + theta);
  _control_set_motor(XDC_TOPRIGHT, -y + x + theta);
  _control_set_motor(XDC_BOTTOMLEFT, y - x + theta);
  _control_set_motor(XDC_BOTTOMRIGHT, -y - x + theta);
}

void control_xdrivecorner_gamer() {
	int y = joystickGetAnalog(1, 3);
  int theta = joystickGetAnalog(1, 1);

  _control_set_motor(XDC_TOPLEFT, y + theta);
  _control_set_motor(XDC_TOPRIGHT, -y + theta);
  _control_set_motor(XDC_BOTTOMLEFT, y + theta);
  _control_set_motor(XDC_BOTTOMRIGHT, -y + theta);
}

void control_xdriveedge() {
	int x = joystickGetAnalog(1, 4);
	int y = joystickGetAnalog(1, 3);
  int delta = joystickGetAnalog(1, 1);

  _control_set_motor(XDR_LEFT, y + delta);
  _control_set_motor(XDR_RIGHT, -y + delta);
  _control_set_motor(XDR_UP, x + delta);
  _control_set_motor(XDR_DOWN, -x + delta);
}
