/** @file EncoderEngine.h
 * @brief Controls a motor via absolute encoder values
 */

#ifndef INU_ABSENGINE_H
#define INU_ABSENGINE_H

#include "inu/wrapper/Motor.h"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.hpp"
#include "inu/util/Stopwatch.hpp"

namespace inu {
namespace engine {

struct EncoderEngineSettings {
	// Amount of acceptable error when the motor is close to the target. In
	// encoder units.
	unsigned int steadyError = 10;

	// Whether or not Execute() will run the motor in the background.
	bool runInBackground = true;

	// Max # of seconds until Execute() quits if the motor doesn't reach the
	// target.
	double timeout = 10.0;

	// Max velocity used to reach the target. This varies per motor, so 100
	// is used to cover all bases.
	unsigned int maxVelocity = 100;
};


class EncoderEngine : public Engine {
public:
	enum COORD {RELATIVE, ABSOLUTE};

	EncoderEngine(inu::port motorPort, COORD mode, EncoderEngineSettings settings);
	virtual void Execute() override;

	/**
	 * @return if motor is considered to be in the "steady state" area. 
	 * This does not mean the motor is still.
	 */
	bool InSteady(); 

	/**
	 * @return if motor is in "steady state" area or time out.
	*/ 
	bool IsFinished();

	/**
	* Halt the program until IsFinished().
	*/ 
	void Wait(); 

private:
	COORD mode;
	EncoderEngineSettings settings;
	inu::Stopwatch lastExecute;
};




}
}


#endif
