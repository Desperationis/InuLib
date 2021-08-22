#include "Controllers.h"
#include "api.h"
#include "pros/api_legacy.h"
#include "pros/misc.h"

using namespace pros::c;

/*
    Task handle to the current_controller; This is automatically managed
    internally in here.
 */
TaskHandle current_controller = NULL;
ubyte control_delay = 20;
float control_scale = 1.0;
controller_t current_controller_pointer = NULL;


void control_set_delay(ubyte delay) {
    control_delay = delay;
}

void control_set_scale(float scale) {
    control_scale = scale;
}

float control_get_scale() {
    return control_scale;
}

controller_t control_get_controller() {
    return current_controller_pointer;
}

bool control_is_running() {
    return current_controller != NULL;
}

/*
   Sets the speed of a motor controlled by a controller; This tries to take
   advantage of slewing and scales the input
 */
void _control_set_motor(tMotor port, int speed) {
    slew_set(port, motor_cap(speed * control_scale));
}

/*
    Task that continuously calls the current controller, spaced out by
    control_delay.
 */
void _control_loop_task(void* parameters) {
    uint32_t time = 0;

    while(1) {
        current_controller_pointer(NULL);
        taskDelayUntil(&time, control_delay);
    }
}

void control_stop() {
    if(control_is_running()) {
        taskDelete(current_controller);
        current_controller = NULL;
        current_controller_pointer = NULL;
    }
}

void control_switch(controller_t task_code) {
    control_stop();
    current_controller = task_create(_control_loop_task, NULL, TASK_PRIORITY_DEFAULT, 64, "Controllerc");
    current_controller_pointer = task_code;
}

// TODO: Fix all controllers to fit with new V5 controller

void control_xdrivecorner(void* parameters) {
    int x = controller_get_analog(CONTROLLER_MASTER, ANALOG_LEFT_X);
    int y = controller_get_analog(CONTROLLER_MASTER,ANALOG_LEFT_Y);
    int theta = controller_get_analog(CONTROLLER_MASTER, ANALOG_LEFT_X);

    _control_set_motor(XDC_TOPLEFT, y + x + theta);
    _control_set_motor(XDC_TOPRIGHT, -y + x + theta);
    _control_set_motor(XDC_BOTTOMLEFT, y - x + theta);
    _control_set_motor(XDC_BOTTOMRIGHT, -y - x + theta);
}

void control_xdrivecorner_gamer(void* parameters) {
    int y = controller_get_analog(CONTROLLER_MASTER,ANALOG_LEFT_Y);
    int theta = controller_get_analog(CONTROLLER_MASTER, ANALOG_LEFT_X);

    _control_set_motor(XDC_TOPLEFT, y + theta);
    _control_set_motor(XDC_TOPRIGHT, -y + theta);
    _control_set_motor(XDC_BOTTOMLEFT, y + theta);
    _control_set_motor(XDC_BOTTOMRIGHT, -y + theta);
}

void control_xdriveedge(void* parameters) {
    int x = controller_get_analog(CONTROLLER_MASTER, ANALOG_LEFT_X);
    int y = controller_get_analog(CONTROLLER_MASTER,ANALOG_LEFT_Y);
    int delta = controller_get_analog(CONTROLLER_MASTER, ANALOG_LEFT_X);

    _control_set_motor(XDR_LEFT, y + delta);
    _control_set_motor(XDR_RIGHT, -y + delta);
    _control_set_motor(XDR_UP, x + delta);
    _control_set_motor(XDR_DOWN, -x + delta);
}
