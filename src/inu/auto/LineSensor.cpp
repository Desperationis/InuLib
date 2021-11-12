#include "inu/auto/LineSensor.h"

using namespace inu;

LineSensor::LineSensor(unsigned int port) : sensor(port) { 
	error = 0;
}

void LineSensor::SetError(int error) {
	this->error = error;
}

unsigned int LineSensor::GetValue() const {
	return sensor.get_value() - error;
}

bool LineSensor::IsLine(unsigned int threshold, bool activeOnBlack) {
	if(activeOnBlack)
		return GetValue() >= threshold;

	return GetValue() <= threshold;
}	
