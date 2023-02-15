/** @file FieldPoint.hpp
 * @brief Represents a point on the VEX field
*/

#ifndef INU_FIELDPOINT_HPP
#define INU_FIELDPOINT_HPP


namespace inu {

struct MathPoint;


struct FieldPoint {
	double x = 0;
	double y = 0;

	FieldPoint();
	FieldPoint(double x, double y);
	FieldPoint(MathPoint point);

	MathPoint toMath();
};


} // namespace inu

#endif
