/** @file SlewEngine.h
 * @brief Controls a motor velocity-wise.
 */

#ifndef INU_SLEWENGINE_H
#define INU_SLEWENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.hpp"
#include "inu/background/BackgroundTask.h"

namespace inu {
namespace engine {

class SlewEngine : public Engine, BackgroundTask {
public:
	SlewEngine(inu::port motorPort);
	~SlewEngine();
	virtual void Execute() override;
	virtual void Shutdown() override;

	void SetSlewRate(uint8_t rate);
	void _Update() override;

private:
	int Interpolate(int start, int end, unsigned int maximum);

private:
	uint8_t slewRate;
	bool enrolled; // memoize
};




}
}


#endif
