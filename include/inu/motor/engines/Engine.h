/** @file Engine.h
 * @brief Interface for all engines
 */

#ifndef INU_ENGINE_H
#define INU_ENGINE_H

namespace inu {
	namespace engine {

		class Engine {
		public:
			/**
			 * Set the target value of whatever the engine is trying to accomplish.
			 * Does not stall.
			 *
			 * @param value Target value for engine.
			 */
			virtual void SetTarget(double value) = 0;

			/**
			 * Run the engine. This may stall depending on how the engine is set up.
			 */
			virtual void Execute() = 0;
		};
	
	}
}


#endif
