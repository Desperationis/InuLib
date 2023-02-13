/** @file Assignment.h
 * @brief Abstract class for all assignments
*/ 

#ifndef INU_ASSIGNMENT_H
#define INU_ASSIGNMENT_H

#include "main.h"
#include "inu/Types.hpp"

namespace inu {

class Assignment {
public:
	// TOOO: Add Controller here
	Assignment();

	/**
	* Runs the assignment and blocks thread until complete.
	*/ 
	virtual void Run() = 0;
};

}

#endif
