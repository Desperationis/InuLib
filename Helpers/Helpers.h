#ifndef HELPERS_HEADER
#pragma systemFile
#define HELPERS_HEADER

/*
 * Helpers.h
 *
 * Helper functions that can be used throughout the library / program.
 *
*/


// Helper Functions
void ResetEncoders();                                                                // Reset chassis' encoder's value to 0.
void SetChassisMotor(byte leftMotorValue, byte rightMotorValue);                     // Sets the chassis speed.
short Clamp(short value);                                                            // Clamps values down to -127 and 127
short Step(short original, short step, short target);                                // Increments a value to a target by maximum fixed amount.
short SlewStep(short original, short step, short target);                            // Only Increments a value to a target by maximum fixed amount if it's a higher value.
bool HasReached(short encoderPort, short value);                                     // Returns if an encoder has passed a threshold.
bool BothHasReached(short enc1, short enc2, short value);                            // Returns if two encoders have passed a threshold.




#endif
