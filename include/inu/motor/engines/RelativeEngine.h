/** @file RelativeEngine.h
 * @brief Controls a motor velocity-wise.
 */

#ifndef INU_RELENGINE_H
#define INU_RELENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.hpp"

namespace inu {
namespace engine {

class RelativeEngine : public Engine {
public:
	RelativeEngine(inu::port motorPort);
	virtual void Execute() override;

	void SetMaxSpeed(uint8_t speed);

private:
	uint8_t maxSpeed;
};




}
}


#endif
