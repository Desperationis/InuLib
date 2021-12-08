/** @file LineSensor.hpp
 * @brief Wrapper for line sensor.
 *
 * Wrapper for line sensor that allows you to "calibrate" the value at
 * compile-time.
 */ 

#ifndef INULINESENSOR_HPP
#define INULINESENSOR_HPP

#include "main.h"
#include "inu/Types.hpp"

namespace inu {
	class LineSensor {
	public:
		/**
		 * @param port Port of the line sensor from 1-8, 'a'-'z', or 'A'-'Z'.
		*/ 
		LineSensor(inu::port port);

		/**
		 * If the sensor has a constant offset relative to other sensors, you
		 * can add that missing value here. The value here will be added when
		 * you get the value of the sensor.
		 *
		 * @param error The overshoot or undershoot in light value.
		*/
		void SetError(int error);

		/**
		 * Gets the value of the sensor.
		 *
		 * @returns The light value read by the sensor.
		*/ 
		int GetValue() const;

		/**
		 * Whether or not the light value read is a line.
		 *
		 * @param threshold The light value that determines the difference
		 * between the line and the background; It should be the midpoint of
		 * their light values.
		 *
		 * @param activeOnBlack Whether or not the line trying to be read is
		 * black on a white background.
		*/ 
		bool IsLine(int threshold, bool activeOnBlack = false);

	private:
		pros::ADILineSensor sensor;
		int error;
	};
}



#endif
