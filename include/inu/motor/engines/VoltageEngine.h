/** @file VoltageEngine.h
 * @brief Controls a motor voltage-wise
 */

#ifndef INU_VOLENGINE_H
#define INU_VOLENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.h"

namespace inu {
namespace engine {

class VoltageEngine : public Engine {
public:
	VoltageEngine(inu::port motorPort);
	virtual void SetTarget(double value);
	virtual void Execute();
private:
	double target;
	inu::Motor motor;
};




}
}


#endif
