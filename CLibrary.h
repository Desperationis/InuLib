/*
 * CLibrary.h
 *
 * A list of declarations that are defined in CLibrary.c
 *
*/

// Setters
void SetLeftMotor(short port);                      					   // Sets the left motor port
void SetRightMotor(short port);                                  // Sets the right motor port
void SetLeftEncoder(short port);                                 // Sets the left encoder port
void SetRightEncoder(short port);                                // Sets the right encoder port
void SetControllerSpeed(double speed);                           // Sets the controller speed of the robot's wheels
void SetAverageDelay(short delayTime);                           // Sets the delay of all tasks

// Getters
short GetLeftMotor();                                            // Gets the left motor port
short GetRightMotor();                                           // Gets the right motor port
short GetLeftEncoder();                                          // Gets the left encoder port
short GetRightEncoder();                                         // Gets the right encoder port
short GetDelay();                                                // Gets the delay of all tasks

// Helper Functions
void ResetEncoders();                                            // Reset chassis' encoder's value to 0.
short Clamp(short value);                                        // Clamps values down to -127 and 127
bool HasReached(short encoderPort, short value);                 // Returns if an encoder has passed a threshold.
bool BothHasReached(short enc1, short enc2, short value);        // Returns if two encoders have passed a threshold.

// Tasks
task LeftArcadeControl();                                        // Control chassis with only the left joystick
task RightArcadeControl();                                       // Control chassis with only the right joystick
task CustomTankControl();                                        // Control chassis with both joysticks like a tank
task GamerControl();                                             // Control chassis with both joysticks like a gamer

// Functions
void MoveUntil(short encoderValue, short Lpow, short Rpow);      // Move chassis based on encoder value
