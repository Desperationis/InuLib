#pragma config(Motor,  port1,           test_motor,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
	Make sure slew is working properly.
*/

#define SLEW_STEP 1 // Make step small enough to be noticable

#include "../Slew.c"

void speedCheck(byte speed) {
	slew_set_motor(test_motor, speed);
	delay(3000);
	slew_set_motor(test_motor, 0);
	delay(5000);
}

task main() {

	startTask(slew_task);

	// You should see the motor ramping up to a slow pace in two directions.
	speedCheck(-60);
	speedCheck(60);

	// You should then see the motor ramping up to the maximum pace in two directions.
	speedCheck(-127);
	speedCheck(127);
}
