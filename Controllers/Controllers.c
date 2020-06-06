#ifndef CONTROLLERS_SOURCE
#define CONTROLLERS_SOURCE
#include "Controllers.h"
#include "../Globals/Globals.h"
#include "../Helpers/Helpers.h"
#include "Slew/Slew.h"

// TODO:
// 		PID Control


// Positive Power turns left motor clockwise. + Forward - Backward

// Left Axle Variables
// Ch4: X <- Ch3: Y Positive Down

// Right Axle Variables
// Ch1: X -> Ch2: Y Positive Down


task LeftArcadeControl() {
	while (true) {
		// Arcade control with left joystick.
		SetMotorSlew( GetLeftMotor(),  Clamp(-vexRT[Ch3] - vexRT[Ch4]) );
		SetMotorSlew( GetRightMotor(),  Clamp(-vexRT[Ch3] + vexRT[Ch4]) );

		delay(GetDelay());
	}
}

task RightArcadeControl() {
	while (true) {
		// Arcade control with right joystick.
		SetMotorSlew( GetLeftMotor(),  Clamp(-vexRT[Ch2] + vexRT[Ch1]) );
		SetMotorSlew( GetRightMotor(),  Clamp(-vexRT[Ch2] - vexRT[Ch1]) );

		delay(GetDelay());
	}
}

task CustomTankControl() {
	while (true) {
		// Tank control with both joysticks.
		SetMotorSlew( GetLeftMotor(),  Clamp(-vexRT[Ch3]) );
		SetMotorSlew( GetRightMotor(),  Clamp(-vexRT[Ch2]) );

		delay(GetDelay());
	}
}

task GamerControl() {
	while (true) {
		// Game control (Similar to controls in racing games)
		// Left Axis: up / down
		// Right Axis: right / left
		SetMotorSlew( GetLeftMotor(), Clamp(-vexRT[Ch3] + vexRT[Ch1]) );
		SetMotorSlew( GetRightMotor(), Clamp(-vexRT[Ch3] - vexRT[Ch1]) );

		delay(GetDelay());
	}
}

#endif
