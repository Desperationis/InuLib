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

/*
 NOTE:
 The side a motor is on must be declared in Motor and Sensor
 Setup in the Drive Motor Side Section.
*/


void _controller_set_left(byte speed) {
	for(byte i = 0; i < 10; i++) {
		if(nMotorDriveSide[i] == driveLeft) {
			motor[i] = speed;
		}
	}
}

void _controller_set_right(byte speed) {
	for(byte i = 0; i < 10; i++) {
		if(nMotorDriveSide[i] == driveRight) {
			motor[i] = speed;
		}
	}
}


/**
 * Arcade control on the left joystick, slewing if possible.
*/
task controller_l_arcade() {
	while (true) {
		_controller_set_left(motor_clamp(-vexRT[Ch3] * 1.3 - vexRT[Ch4])); // One will ALWAYS be slightly slower than the other due to the stick being slightly left / right
		_controller_set_right(motor_clamp(-vexRT[Ch3] * 1.3 + vexRT[Ch4]));
		delay(TASK_DELAY);
	}
}


/**
 * Arcade control on the right joystick, slewing if possible.
*/
task controller_r_arcade() {
	while (true) {
		_controller_set_left(motor_clamp(vexRT[Ch2] * 1.3 + vexRT[Ch1]));
		_controller_set_right(motor_clamp(-vexRT[Ch2] * 1.3 - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


/**
 * Tank control on both joysticks, slewing if possible.
*/
task controller_tank() {
	while (true) {
		_controller_set_left(-vexRT[Ch3] * 1.3);
		_controller_set_right(-vexRT[Ch2] * 1.3);

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
		_controller_set_left(motor_clamp(-vexRT[Ch3] * 1.3 + vexRT[Ch1]));
		_controller_set_right(motor_clamp(-vexRT[Ch3] * 1.3 - vexRT[Ch1]));

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
		_controller_set_left(motor_clamp(-controllerPacket.data[AXISY] * 1.3 + controllerPacket.data[AXISX]));
		_controller_set_right(motor_clamp(-controllerPacket.data[AXISY] * 1.3 - controllerPacket.data[AXISX]));
		delay(TASK_DELAY);
	}
}


#endif
