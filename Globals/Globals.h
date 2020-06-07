#pragma systemFile
#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

/*
 * Globals.h
 *
 * Setter / Getter System for global variables and structs.
 * This system was made in order to be compatible with my C++ project
 * RobotCSimulator (https://github.com/Desperationis/RobotCSimulator)
*/

enum MOTOR {
	LEFT = 0,
	RIGHT
};


/*
 * [SETUP]
 *
 * Set the motor port of the left motor. Needed for library to function properly.
*/
void SetLeftMotor(tMotor port);


/*
 * [SETUP]
 *
 * Set the motor port of the right motor. Needed for library to function properly.
*/
void SetRightMotor(tMotor port);


/*
 * [SETUP]
 *
 * Set the sensor port of the left encoder. Needed for PID controller to function properly.
*/
void SetLeftEncoder(tSensors port);

/*
 * [SETUP]
 *
 * Set the sensor port of the right encoder. Needed for PID controller to function properly.
*/
void SetRightEncoder(tSensors port);


/*
 * [SETUP]
 *
 * Set the maximum speed of any slewed motor [0...1].
 * PID, Slew, and regular controllers automatically use slewed.
*/
void SetMaxSpeed(float speed);


/*
 * [SETUP]
 *
 * Set the delay of each task in this library. Prevents the Cortex from heating up too much.
*/
void SetAverageDelay(ubyte delayTime);


/*
 * Returns the motor port of the left motor.
*/
tMotor GetLeftMotor();


/*
 * Returns the motor port of the right motor.
*/
tMotor GetRightMotor();



/*
 * Returns the sensor port of the left encoder.
*/
tSensors GetLeftEncoder();


/*
 * Returns the sensor port of the right encoder.
*/
tSensors GetRightEncoder();


/*
 * Returns the delay for all the library's tasks.
*/
ubyte GetDelay();


/*
 * Returns the maximum slew speed of the robot.
*/
double GetMaxSpeed();

#endif
