#ifndef SLEWMOTOR_H
#define SLEWMOTOR_H


#include "main.h"

class SlewSystem;


/**
 * Slews a motor.
*/
class SlewMotor {
public:
	// TODO: Add doxygen compliant comments
	SlewMotor(unsigned int port);

	void Set(unsigned int speed);

	void SetRate(unsigned int rate);

private:
	// Interpolates between two values by a maximum amount
	unsigned int Interpolate(unsigned int start, unsigned int end, 
					unsigned int maximum);
};


#endif
