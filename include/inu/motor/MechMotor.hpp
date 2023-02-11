/** @file MechMotor.hpp
 * @brief Allows the use of "engines" that control the motor.
 *
 * Allows the use of "engines" that control the motor in various different ways.
 * Supports engines that halt the program.
 */

#ifndef INU_DYNMOTOR_HPP
#define INU_DYNMOTOR_HPP

#include <memory>
#include "main.h"
#include "inu/InuException.hpp"
#include "inu/Types.hpp"
#include "inu/motor/engines/Engine.hpp"

namespace inu {


class MechMotor {
public:
	MechMotor(inu::port port) {
		this->port = port;
		currentEngine = nullptr;
	}

	template<typename T, typename ... A>
	void ChangeEngine(A...args) {
		if (currentEngine)
			currentEngine->Shutdown();

		currentEngine.reset();
		auto tmp = std::make_shared<T>(port, args...);
		currentEngine = std::dynamic_pointer_cast<inu::engine::Engine>(tmp);

		if (currentEngine == nullptr)
			throw InuException("MechMotor.hpp: Unable to cast to inu::engine::Engine");
	}

	template<typename T>
	std::weak_ptr<T> GetEngine() {
		auto engine = std::dynamic_pointer_cast<T>(currentEngine);

		if (engine == nullptr)
			throw InuException("MechMotor.hpp: Unable to cast to child class");

		return std::weak_ptr<T>(engine);
	}


	void SetTarget(double value) {
		currentEngine->SetTarget(value);
	}

	void Execute() {
		currentEngine->Execute();
	}

	void Shutdown() {
		currentEngine->Shutdown();
	}

private:
	inu::port port;
	std::shared_ptr<inu::engine::Engine> currentEngine;

};



}

#endif
