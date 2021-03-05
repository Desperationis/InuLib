#pragma systemFile
#ifndef CONTROLLERS_SOURCE
#define CONTROLLERS_SOURCE

#ifndef TASK_DELAY
	#define TASK_DELAY 20
#endif

#include "Helpers.c"
#include "Slew.c"
#include "Serial.c"

/*
	Diego's Controller Tips:

	Positive Power turns left motor clockwise. + Forward - Backward

	Left Axle Variables
	Ch4: X Positive Left
	Ch3: Y Positive Down

	Right Axle Variables
	Ch1: X Positive Right
	Ch2: Y Positive Down
*/

#ifndef LEFT_MOTOR_PORT
	#define LEFT_MOTOR_PORT port1
#endif

#ifndef RIGHT_MOTOR_PORT
	#define RIGHT_MOTOR_PORT port1
#endif

/**
 * Arcade control on the left joystick, slewing if possible.
*/
task controller_l_arcade() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  motor_clamp(-vexRT[Ch3] - vexRT[Ch4]));
		slew_set_motor(RIGHT_MOTOR_PORT, motor_clamp(-vexRT[Ch3] + vexRT[Ch4]));
		delay(TASK_DELAY);
	}
}


/**
 * Arcade control on the right joystick, slewing if possible.
*/
task controller_r_arcade() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  motor_clamp(vexRT[Ch2] + vexRT[Ch1]));
		slew_set_motor(RIGHT_MOTOR_PORT, motor_clamp(-vexRT[Ch2] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


/**
 * Tank control on both joysticks, slewing if possible.
*/
task controller_tank() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  -vexRT[Ch3]);
		slew_set_motor(RIGHT_MOTOR_PORT, -vexRT[Ch2]);

		delay(TASK_DELAY);
	}
}


/**
 * Racecar-like controls, slewing if possible.
*/
task controller_gamer() {
	while (true) {
		// Left Axis: up / down
		// Right Axis: right / left
		slew_set_motor(LEFT_MOTOR_PORT,  motor_clamp(-vexRT[Ch3] + vexRT[Ch1]));
		slew_set_motor(RIGHT_MOTOR_PORT, motor_clamp(-vexRT[Ch3] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}

/**
 * Racecar-like controls, slewing if possible, using a PS4 controller.
*/
task controller_serial_gamer() {
	serial_configure();
	packet_t controllerPacket;

	while (true) {
		serial_update(controllerPacket);
		slew_set_motor(LEFT_MOTOR_PORT,  motor_clamp(-controllerPacket.data[AXISY] + controllerPacket.data[AXISX]));
		slew_set_motor(RIGHT_MOTOR_PORT, motor_clamp(-controllerPacket.data[AXISY] - controllerPacket.data[AXISX]));
		delay(TASK_DELAY);
	}
}


#endif
