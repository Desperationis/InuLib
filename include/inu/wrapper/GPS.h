/** @file GPS.h
 * @brief Extension of pros::gps class
 *
 * A extension of the pros::gps class.
*/ 

#ifndef INUGPS_HPP
#define INUGPS_HPP

#include "main.h"
#include "inu/Types.hpp"

namespace inu {
	class GPS {
	public:

		GPS(inu::port port);

        /**
         * Sets the offset of the GPS relative to the chassis' turning
         * point. Measured in meters.
         *
         * @param xOffset X-axis meters from the turning point
		 * @param yOffset Y-axis meters from the turning point
         */
        void SetOffset(double xOffset, double yOffset);

        /**
         * If GPS is not mounted facing forward of the robot, offset the
         * degrees by adding this amount.
         *
         * @param hOffset Amount in degrees
         */
        void SetHeadingOffset(double headingOffset);

        /**
         * Sets the initial pose of the robot from the center of the field.
         * This is used to avoid deadzones in the field's GPS strips.
         *
         * @param xInitial X-axis meters from the field center
         * @param yInitial Y-axis meters from the field center
         * @param heading Heading of the robot in degrees
         */
        void SetInitialPose(double xInitial, double yInitial, double heading);

        /**
         * Sets the GPS sensor's data rate in milliseconds. Only applies to IMU
         * on GPS.
         *
         * @param rate Data rate in milliseconds (minimum 5ms)
         */
        void SetDataRate(std::int32_t rate);

        /**
         * Get the possible Root Mean Squared error, in meters, of the GPS
         * position.
         *
         * @return Possible RMS in meters for GPS position.
         */
        double GetError() const;

        /**
         * @return Struct with position, roll, yaw, and pitch of GPS.
         */
        pros::c::gps_status_s_t GetInfo() const;

	
        /**
         * @return The heading of the GPS in degrees. 
         */
		double GetHeading() const;

	private:
		pros::GPS sensor;
		double headingOffset;

	};

}

#endif
