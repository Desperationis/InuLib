#ifndef GLOBALS_HEADER

#pragma systemFile
#define GLOBALS_HEADER

/*
 * Globals.h
 *
 * Setter / Getter System for global variables.
 * Used for avoiding the use of extern.
 *
*/

// Setters
void SetLeftMotor(short port);                      					   // Sets the left motor port
void SetRightMotor(short port);                                  // Sets the right motor port
void SetLeftEncoder(short port);                                 // Sets the left encoder port
void SetRightEncoder(short port);                                // Sets the right encoder port
void SetControllerSpeed(double speed);                           // Sets the controller speed of the robot's wheels
void SetAverageDelay(short delayTime);                           // Sets the delay of all tasks
void SetSlewStep(short step);                                    // Sets the step amount for slew controller

// Getters
short GetLeftMotor();                                            // Gets the left motor port
short GetRightMotor();                                           // Gets the right motor port
short GetLeftEncoder();                                          // Gets the left encoder port
short GetRightEncoder();                                         // Gets the right encoder port
short GetDelay();                                                // Gets the delay of all tasks
short GetSlewStep();                                             // Gets the step amount of slew controller
double GetControllerSpeed();                                     // Gets the controller speed

#endif
