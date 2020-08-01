#pragma systemFile
#ifndef HELPERS_SOURCE
#define HELPERS_SOURCE


/**
 * Returns the maximum of two values.
*/
short Max(short a, short b) {
	return a > b ? a: b;
}


/**
 * Returns the minimum of two values.
*/
short Min(short a, short b) {
	return a < b ? a: b;
}


/**
 * Constrains a value into a range.
*/
short Clamp(short value, short min, short max) {
	return Max(Min(value, max), min);
}


/**
 * Ensures a value never surpasses the motor
 * speed limit.
*/
short MotorClamp(short value) {
	return Clamp(value, -127, 127);
}


/**
 * Linearly interpolates between two values by a
 * maximum value.
*/
short Step(short original, short step, short target){
	if(abs(original - target) > step){
		return original + (sgn(target - original) * step);
	}
	return target;
}


/**
 * Determines if a value has reached a target within
 * a specified range.
*/
bool HasReached(short original, short target, short range) {
	return abs(original) - abs(target) <= range;
}

#endif
