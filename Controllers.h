#pragma systemFile
#ifndef CONTROLLERS_SOURCE
#define CONTROLLERS_SOURCE

#include "Helpers.h"
#include "Slew.h"

/*
	Diego's Controller Tips:

	Positive Power turns left motor clockwise. + Forward - Backward

	Left Axle Variables
	Ch4: X <- Ch3: Y Positive Down

	Right Axle Variables
	Ch1: X -> Ch2: Y Positive Down

*/


/**
 * Arcade control on the left joystick.
 * Tries to slew if possible.
*/
task LeftArcadeControl() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3] - vexRT[Ch4]));
		slew_set_motor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch3] + vexRT[Ch4]));
		delay(TASK_DELAY);
	}
}


/**
 * Arcade control on the right joystick.
 * Tries to slew if possible.
*/
task RightArcadeControl() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  MotorClamp(vexRT[Ch2] + vexRT[Ch1]));
		slew_set_motor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch2] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


/**
 * Tank control!
 * Tries to slew if possible.
*/
task CustomTankControl() {
	while (true) {
		slew_set_motor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3]));
		slew_set_motor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch2]));

		delay(TASK_DELAY);
	}
}


/**
 * Racecar-like controls.
 * Tries to slew if possible.
*/
task GamerControl() {
	while (true) {
		// Left Axis: up / down
		// Right Axis: right / left
		slew_set_motor(LEFT_MOTOR_PORT,  MotorClamp(-vexRT[Ch3] + vexRT[Ch1]));
		slew_set_motor(RIGHT_MOTOR_PORT, MotorClamp(-vexRT[Ch3] - vexRT[Ch1]));

		delay(TASK_DELAY);
	}
}


#endif
