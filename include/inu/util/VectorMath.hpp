/** @file VectorMath.hpp
 * @brief Math for Vectors
*/

#ifndef INU_VECTORMATH_HPP
#define INU_VECTORMATH_HPP

#include "main.h"
#include "inu/util/Vector.hpp"


namespace inu {


class VectorMath {
public:
	/**
	* Given two vectors A and B defined in a coordinate plane C, transform
	* B such that the new coordinate plane is in terms of A.
	*
	* @return Vector where 0 theta is A. Magnitude of Vector is B. 
	*/
	static Vector RelativeVector(Vector a, Vector b) {
		double aRad = a.Radians();
		double bRad = b.Radians();
		double bLength = b.Magnitude();

		double difference = bRad - aRad;

		return Vector::FromAngle(difference, bLength);
	}

};





} // namespace inu

#endif
