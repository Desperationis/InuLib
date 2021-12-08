#include "inu/wrapper/InertialSensor.h"
#include "inu/InuException.hpp"
#include "pros/apix.h"

using namespace inu;
using pros::c::v5_device_e_t::E_DEVICE_IMU;

InertialSensor::InertialSensor(inu::port port) : sensor(port) {
	if(port < 1 || port > 20) 
		throw InuException("InertialSensor.h: Port must be between 1-20.");
	
	if(pros::c::registry_get_plugged_type(port - 1) != E_DEVICE_IMU)
		throw InuException("InertialSensor.h: Port is not a IMU sensor.");

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

