/** @file AutoXChassisBuilder.h
 * @brief Builder for AutoXChassis instances.
 *
 * Builder for AutoXChassis instances.
*/ 


#ifndef AUTOXCHASSIS_BUILDER_H
#define AUTOXCHASSIS_BUILDER_H

#include "inu/auto/chassis/AutoChassisBuilder.h"
#include "inu/wrapper/Motor.h"
#include <memory>
#include <cstdint>
#include "inu/Types.hpp"

namespace inu {
	class AutoXChassis;

	class AutoXChassisBuilder : public AutoChassisBuilder {
	public:
		AutoXChassisBuilder();

		~AutoXChassisBuilder();

		void SetMotors(inu::port tl, inu::port tr, inu::port bl, inu::port br);

		std::weak_ptr<inu::Motor> GetTopleft() const;

		std::weak_ptr<inu::Motor> GetTopright() const;

		std::weak_ptr<inu::Motor> GetBottomleft() const;

		std::weak_ptr<inu::Motor> GetBottomright() const;

		std::shared_ptr<inu::AutoXChassis> Build();

	private:
		bool motorPortsDefined;
		std::shared_ptr<inu::Motor> topleft, topright;
		std::shared_ptr<inu::Motor> bottomleft, bottomright;
	};
}


#endif
