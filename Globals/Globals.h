#ifndef GLOBALS_HEADER
#define GLOBALS_HEADER

/*
 * Globals.h
 *
 * Setter / Getter System for global variables and structs.
 * This system was made in order to be compatible with my C++ project
 * RobotCSimulator (https://github.com/Desperationis/RobotCSimulator)
 *
 * If you don't need to simulate code, RobotC automatically externs all
 * varibales, so it's fine to not use this.
*/

typedef struct {
	double kP;
	double kI;
	double kD;
	short proportion;
	short integral;
	short derivative;
	short pastError;
} PIDInfo;


/*
 * Set the motor port of the left motor. Needed for library to fucntion properly.
*/
void SetLeftMotor(tMotor port);


/*
 * Set the motor port of the right motor. Needed for library to fucntion properly.
*/
void SetRightMotor(tMotor port);


/*
 * Set the sensor port of the left encoder. Needed for PID controller to function properly.
*/
void SetLeftEncoder(tSensors port);

/*
 * Set the sensor port of the right encoder. Needed for PID controller to function properly.
*/
void SetRightEncoder(tSensors port);


/*
 * Set the maximum speed of the robot. Only applies to motors that have been slewed.
*/
void SetControllerSpeed(double speed);


/*
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
double GetControllerSpeed();

#endif
