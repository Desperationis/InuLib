#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "main.h"

class PIDSystem;


struct PIDMotor {
	PIDMotor(unsigned int port);

	~PIDMotor();

	void Set(unsigned int speed);

	void SetP(float p);

	void SetI(float i);

	void SetD(float d);

	unsigned int GetPort();

	unsigned int GetTargetSpeed();

	float GetP();

	float GetI();

	float GetD();

};


#endif
