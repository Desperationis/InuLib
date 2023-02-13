/** @file DiskAssignment.h
 * @brief Collects disks in front of the robot
*/ 

#ifndef INU_DISKASSIGNMENT_HPP
#define INU_DISKASSIGNMENT_HPP

#include "main.h"
#include "inu/Types.hpp"
#include "inu/nav/assignment/Assignment.h"
#include "inu/wrapper/VisionSensor.h"

namespace inu {

class DiskAssignment : public Assignment {
public:
	/**
	 * @param port Port of the vision sensor
	*/ 
	DiskAssignment(inu::VisionSensor sensor);

	virtual void Run();		

private:
	inu::VisionSensor sensor;

};

} // namespace inu

#endif
