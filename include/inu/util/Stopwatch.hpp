/** @file Stopwatch.hpp
 * @brief Records time elapsed on the cortex.
*/

#ifndef INU_STOPWATCH_H
#define INU_STOPWATCH_H

#include "main.h"


namespace inu {



class Stopwatch {
public:
	Stopwatch() {
		marker = 0;
	}

	/**
	 * Marks down the current position in time.
	*/ 
	void Mark() {
		marker = pros::millis();
	}

	/**
	* @return Elapsed milliseconds since last marker.
	*/ 
	uint32_t GetElapsed() {
		return pros::millis() - marker;
	}


private:
	uint32_t marker;
};





} // namespace inu

#endif
