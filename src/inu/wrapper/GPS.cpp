#include "inu/wrapper/GPS.h"
#include "inu/InuException.hpp"
#include "inu/util/TrigMath.hpp"
#include "pros/apix.h"

using namespace inu;

GPS::GPS(inu::port port) : sensor(port) {
	if(port < 1 || port > 20)
		throw InuException("GPS.h: Port must be between 1-20.");

	if(pros::c::registry_get_plugged_type(port - 1) != pros::c::E_DEVICE_GPS)
		throw InuException("GPS.h: Port is not a GPS.");

	headingOffset = 0;
}

void GPS::SetOffset(double xOffset, double yOffset) {
	sensor.set_offset(xOffset, yOffset);
}

void GPS::SetHeadingOffset(double headingOffset) {
	this->headingOffset = headingOffset;
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
	double heading = sensor.get_heading() + headingOffset;

	// Clamp to [0, 360)
	heading = TrigMath::Wrap360(heading);

	return heading;
}
