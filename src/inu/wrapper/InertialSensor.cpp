#include "inu/wrapper/InertialSensor.h"
#include "inu/InuException.hpp"

using namespace inu;

InertialSensor::InertialSensor(inu::port port) : sensor(port) {
	if(port < 1 || port > 20) 
		throw InuException("InertialSensor.h: Port must be between 1-20.");
	this->port = port;
}

void InertialSensor::Calibrate() const {
	sensor.reset();
}

double InertialSensor::GetRotation() const {
	return sensor.get_rotation();
}

void InertialSensor::TareRotation() const {
	sensor.tare_rotation();
}

inu::port InertialSensor::GetPort() const {
	return port;
}

