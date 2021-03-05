#pragma systemFile
#ifndef HELPERS_SOURCE
#define HELPERS_SOURCE

#ifndef TASK_DELAY
	#define TASK_DELAY 20
#endif

/**
 * Returns the maximum of two values.
*/
short max(short a, short b) {
	return a > b ? a: b;
}


/**
 * Returns the minimum of two values.
*/
short min(short a, short b) {
	return a < b ? a: b;
}


/**
 * Constrains a value into a range.
*/
short clamp(short value, short min_val, short max_val) {
	return max(min(value, max_val), min_val);
}


/**
 * Ensures a value never surpasses the motor speed limit.
*/
short motor_clamp(short value) {
	return clamp(value, -127, 127);
}


/**
 * Determines if a value has reached a target within a specified range.
*/
bool has_reached(short original, short target, short range) {
	return abs(abs(original) - abs(target)) <= range;
}

#endif
