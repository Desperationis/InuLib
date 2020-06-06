#ifndef HELPERS_SOURCE
#define HELPERS_SOURCE
#include "../Globals/Globals.h"
#include "Helpers.h"



void ResetEncoders() {
	SensorValue[GetLeftEncoder()] = 0;
	SensorValue[GetRightEncoder()] = 0;
}

short Clamp(short value) {
	// Clamps integers to maximum motor value; 127
	if (fabs(value) > 127) {
			return 127 * sgn(value);
	}
	return value;
}

short Step(short original, short step, short target){
	if(abs(original - target) > step){
		// Add an amount that gets us closer to the target
		// value if difference exceeds maximum step value.
		if(original > target) {
			return original - step;
		}
		return original + step;
	}

	// Return target value if difference is less
	// than maximum step value
	return target;
}

short SlewStep(short original, short step, short target){
	// Snap to target if the motor is slowing down and
	// doesn't change direction.
	if(fabs(target) < fabs(original) && sgn(target) == sgn(original)) {
			return target;
	}
	return Step(original, step, target);
}

bool HasReached(short encoderPort, short value) {
	return fabs(SensorValue[encoderPort]) > value;
}

bool BothHasReached(short encoder1, short encoder2, short value) {
	return HasReached(encoder1, value) && HasReached(encoder2, value);
}

#endif
