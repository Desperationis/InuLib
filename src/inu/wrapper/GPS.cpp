#include "inu/wrapper/GPS.h"
#include "inu/InuException.hpp"
#include "pros/apix.h"

using namespace inu;

GPS::GPS(inu::port port) : sensor(port) {
	if(port < 1 || port > 20)
		throw InuException("GPS.h: Port must be between 1-20.");

	if(pros::c::registry_get_plugged_type(port - 1) != pros::c::E_DEVICE_GPS)
		throw InuException("GPS.h: Port is not a GPS.");
}

void GPS::SetOffset(double xOffset, double yOffset) {
	sensor.set_offset(xOffset, yOffset);
}

void GPS::SetInitialPose(double xInitial, double yInitial, double heading) {
	sensor.set_position(xInitial, yInitial, heading);
}

void GPS::SetDataRate(std::int32_t rate) {
	sensor.set_data_rate(rate);
}

double GPS::GetError() const {
	return sensor.get_error();
}

pros::c::gps_status_s_t GPS::GetInfo() const {
	return sensor.get_status();
}

double GPS::GetHeading() const {
	return sensor.get_heading();
}
