/** @file InertialSensor.h
 * @brief Wrapper for inertial sensor.
*/

#ifndef INUINERTIALSENSOR_H
#define INUINERTIALSENSOR_H

#include "main.h"
#include "pros/imu.hpp"
#include "inu/Types.hpp"
#include <cstdint>

namespace inu {
	class InertialSensor {
	public:
		/**
		 * @param port Port between 1-20.
		*/ 
		InertialSensor(inu::port port);

		/**
		 * Calibrates the Inertial sensor; Stalls for about 2 seconds.
		*/ 
		void Calibrate() const;

		/**
		 * @returns The unbounded absolute rotation of the InertialSensor
		 * relative to the Z axis.
		*/ 
		double GetRotation() const;

		/**
		 * Tares rotation.
		*/ 
		void TareRotation() const;

		/**
		 * @returns The port of this inertial sensor.
		*/ 
		inu::port GetPort() const;


	private:
		pros::Imu sensor;
		inu::port port;
	};
}

#endif
