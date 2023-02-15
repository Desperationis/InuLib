/** @file FieldController.h
 * @brief Controls a chassis in relation to the field (with GPS).
 */

#ifndef INU_FIELDCONTROLLER_H
#define INU_FIELDCONTROLLER_H

#include "main.h"
#include "inu/Types.hpp"
#include "inu/chassis/XChassis.h"
#include "inu/wrapper/GPS.h"
#include <memory>

namespace inu {

struct PIDProfile;

class FieldController {
public:
	/**
	 * @param chassis XChassis to control
	*/ 
	FieldController(std::shared_ptr<inu::XChassis> chassis, inu::GPS gps);

	/**
	 * Halts program until robot turns to a specific point on the field.
	 */
	void LookAt(double x, double y);

	/**
	 * Turn to a specific direction, in degrees.
	 */ 
	void TurnTo(double degrees);


	/**
	* Move the robot to a specific position on the field. 
	*
	* @param align Whether or not to align the robot to the direction of travel.
	*/ 
	void LinearTo(double x, double y, bool align = false);


	friend std::ostream& operator<<(std::ostream& os, const FieldController& fc);

private:
	/**
	* Calculate turn voltage need to turn a certain heading smoothly.
	* 
	* @param heading Target heading in degrees
	* @param profile PIDProfile to turn by
	* 
	* @return Turn voltage
	*/ 
	double CalcTurnVol(double heading, PIDProfile profile);

private:
	std::shared_ptr<inu::XChassis> chassis;
	inu::GPS gps;
};

std::ostream& operator<<(std::ostream& os, const inu::FieldController& fc);

} // namespace inu



#endif
