#ifndef SLEWMOTOR_H
#define SLEWMOTOR_H


#include "main.h"

class SlewSystem;


// TODO: Turn this into a struct as it
// only holds data


/**
 * Slews a motor.
*/
struct SlewMotor {
public:
	// TODO: Add doxygen compliant comments
	SlewMotor(unsigned int port);

	~SlewMotor();

	void Set(unsigned int speed);

	void SetRate(unsigned int rate);

	unsigned int GetPort();

	unsigned int GetRate();

	unsigned int GetTargetSpeed();

private:
	unsigned int port, rate, targetSpeed;
};


#endif
