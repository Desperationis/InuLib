#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <API.h>
#include "Motor.h"
#include "Slew.h"

/*
    Configure chassis motors here; The value of each enum represents the motor
    port. The functions that use these enums follow the same format:

    control_{name} (uses) -> enum {NAME}_PORTS

    If the function has a second word, use this format:

    control_{name}_{moreinfo} (uses) -> enum {NAME}_{PORTS}

    Feel free to change the order of enums, if you need to.
*/
enum XDRIVECORNER_PORTS {XDC_BOTTOMLEFT = 1, XDC_TOPRIGHT, XDC_TOPLEFT, XDC_BOTTOMRIGHT = 10};
enum XDRIVEEDGE_PORTS {XDR_LEFT = 1, XDR_RIGHT, XDR_UP, XDR_DOWN = 10};

typedef void (*controller_t)(void);

/*
    Switch to a controller that is a parameter-less function of type void. This
    function will be internally looped by taskDelayUntil. If no controller is
    running, this will immediately start the function. The thread handle for
    this is managed internally.
*/
void control_switch(controller_t task_code);

/*
    Set the delay used to loop all controllers; By default, this is set to 20.
    Lowering it is pointless as motors update at this frequency. Higher delays
    don't actually have that much of a difference if slewing is on.
*/
void control_set_delay(ubyte delay);

/*
    Set a float that multiplies the input used for a controller to make it more
    or less sensitive. By default, this is set to 1.0.
*/
void control_set_scale(float scale);

/*
    Get the current scale that is used to multiply input. This is handy if you
    are creating your own controllers.
*/
float control_get_scale();

/*
    Return a function pointer to the current controller, return NULL if there is
    no controller or it was stopped. This is intended to be used for comparison
    operations.
*/
controller_t control_get_controller();

/*
    Whether or not there is a controller currently running.
*/
bool control_is_running();

/*
    Stop the current controller, if running.
*/
void control_stop();


// CONTROLLERS:

/*
	Control chassis via an xdrive configuration where the corners are the
	wheels. Left joystick is for movement, right for turning. This assumes that,
	when all motors are powered with a positive value via the Motor module, the
	robot turns clockwise. This will try to slew motors if possible.
*/
void control_xdrivecorner();

/*
    Control chassis via an xdrive configuration where the corners are the
    wheels. Left joystick is for forward / backward, right for turning; Kind of
    like a racing game. This assumes that, when all motors are powered with a
    positive value via the Motor module, the robot turns clockwise. This will
    try to slew motors if possible.
*/
void control_xdrivecorner_gamer();


/*
	Control chassis via an xdrive configuration where the edges are the wheels;
	The "front" of the robot is a wheel. Left joystick is for movement, right
	for turning. This assumes that, when all motors are powered with a positive
	value via the Motor module, the robot turns clockwise. This will try to slew
	motors if possible.
*/
void control_xdriveedge();

/*
	Control chassis via an xdrive configuration where the corners are the
	wheels. Left joystick is for movement, right for turning. This uses serial
	input via the serial module and assumes that the controller input of
	remoteTransmitter.py matches that of the VEXnet controller. This will try to
	slew motors if possible.
*/
void control_xdrivecorner_serial();


#endif
