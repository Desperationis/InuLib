/** @file Engine.hpp
 * @brief Abstract engine for all engines
 */

#ifndef INU_ENGINE_H
#define INU_ENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"

namespace inu {
namespace engine {

class Engine {
public:
	Engine(inu::port port) : motor(port) {}

	/**
	* Set the target value of whatever the engine is trying to accomplish.
	* Does not stall.
	*
	* @param value Target value for engine.
	*/
	virtual void SetTarget(double value) {
		target = value;
	}

	/**
	* Run the engine. This may stall depending on how the engine is set up.
	*/
	virtual void Execute() = 0;

	/**
	 * Completely cuts power to the motor to stop it. Engine will completely
	 * lose control over the motor until Execute() is called again.
	 */
	virtual void Shutdown() {
		motor.Move(0);
	}

protected:
	inu::Motor motor;
	double target;
};



} // namespace engine
} // namespace inu

#endif
