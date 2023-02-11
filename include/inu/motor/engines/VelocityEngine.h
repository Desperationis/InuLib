/** @file VelocityEngine.h
 * @brief Controls a motor velocity-wise.
 */

#ifndef INU_VELENGINE_H
#define INU_VELENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.h"

namespace inu {
namespace engine {

class VelocityEngine : public Engine {
public:
	VelocityEngine(inu::port motorPort);
	virtual void SetTarget(double value);
	virtual void Execute();
private:
	double target;
	inu::Motor motor;
};




}
}


#endif
