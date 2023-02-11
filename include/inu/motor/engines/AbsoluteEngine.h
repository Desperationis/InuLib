/** @file AbsoluteEngine.h
 * @brief Controls a motor via absolute encoder values
 */

#ifndef INU_ABSENGINE_H
#define INU_ABSENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.hpp"

namespace inu {
namespace engine {

class AbsoluteEngine : public Engine {
public:
	AbsoluteEngine(inu::port motorPort);
	virtual void Execute() override;

	void SetMaxSpeed(uint8_t speed);

private:
	uint8_t maxSpeed;
};




}
}


#endif
