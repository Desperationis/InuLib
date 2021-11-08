/** @file Variant.hpp
 * @brief Returns a value that varies over time
 *
 * Returns a value that varies over time.
 */ 

#include "pros/imu.hpp"
#include "main.h"

#ifndef DOUBLEVARIANT_HPP
#define DOUBLEVARIANT_HPP


namespace inu {
	// botched code; fix this later

	struct DoubleVariant {
	public:
		DoubleVariant(pros::Imu* gyro) {
			this->gyro = gyro;
		}

		double Return() {
			return gyro->get_rotation();
		}


	private:
		pros::Imu* gyro;
	};

}
#endif

