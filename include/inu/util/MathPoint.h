/** @file MathPoint.hpp
 * @brief Represents a point in 
*/

#ifndef INU_MATHPOINT_HPP
#define INU_MATHPOINT_HPP

namespace inu {

struct FieldPoint;


struct MathPoint {
	double x = 0;
	double y = 0;

	MathPoint();
	MathPoint(double x, double y);
	MathPoint(FieldPoint point);

	FieldPoint toField();
};


} // namespace inu

#endif
