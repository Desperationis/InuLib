#ifndef HELPERS_SOURCE

#include "../Globals/Globals.h"
#include "Helpers.h"
#define HELPERS_SOURCE



// Helper Functions
void ResetEncoders() {
	SensorValue[GetLeftEncoder()] = 0;
	SensorValue[GetRightEncoder()] = 0;
}

short Clamp(short value) {
	// Clamps integers to maximum motor value; 127
	if (value > 127) {
		return 127;
	}
	if (value < -127) {
		return -127;
	}
	return value;
}

short Step(short original, short step, short target){
	if(abs(original - target) > step){
		if(original > target) {
			return original - step;
		}
		return original + step;
	}
	return target;
}

short SlewStep(short original, short step, short target){
	if(abs(original - target) > step){
		// Ignore if target is "less" of a motor power than original
		if(abs(target) < abs(original) && target < 0 && original < 0) {
			return target;
		}
		if(abs(target) < abs(original) && target > 0 && original > 0) {
			return target;
		}
		return Step(original, step, target);
	}
	return target;
}

bool HasReached(short encoderPort, short value) {
	return abs(SensorValue[encoderPort]) > value;
}

bool BothHasReached(short enc1, short enc2, short value) {
	return HasReached(enc1, value) && HasReached(enc2, value);
}

#endif
