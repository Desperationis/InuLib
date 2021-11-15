/** @file AutoXChassisBuilder.h
 * @brief Builder for AutoXChassis instances.
 *
 * Builder for AutoXChassis instances.
*/ 


#ifndef AUTOXCHASSIS_BUILDER_H
#define AUTOXCHASSIS_BUILDER_H

#include "inu/auto/chassis/AutoChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/wrapper/Motor.h"
#include "inu/motor/background/SlewMotor.h"
#include <memory>

namespace inu {
	class AutoXChassisBuilder : public AutoChassisBuilder {
	public:
		AutoXChassisBuilder() {
			motorPortsDefined = false;
		}

		~AutoXChassisBuilder() {
			topleft.reset();
			topright.reset();
			bottomleft.reset();
			bottomright.reset();
		}


		void SetMotors(int tl, int tr, int bl, int br) {
			topleft.reset(new inu::Motor(std::abs(tl)));
			if (tl < 0) topleft->SetReversed(true);

			topright.reset(new inu::Motor(std::abs(tr)));
			if (tr < 0) topright->SetReversed(true);

			bottomleft.reset(new inu::Motor(std::abs(bl)));
			if (bl < 0) bottomleft->SetReversed(true);

			bottomright.reset(new inu::Motor(std::abs(br)));
			if (br < 0) bottomright->SetReversed(true);

			motorPortsDefined = true;
		}

		std::weak_ptr<inu::Motor> GetTopleft() const { 
			return topleft; 
		}

		std::weak_ptr<inu::Motor> GetTopright() const {
		   	return topright; 
		}

		std::weak_ptr<inu::Motor> GetBottomleft() const { 
			return bottomleft; 
		}

		std::weak_ptr<inu::Motor> GetBottomright() const { 
			return bottomright; 
		}

		std::shared_ptr<inu::AutoXChassis> Build() {
			if(!motorPortsDefined) {
				return nullptr;
			}

			return std::shared_ptr<inu::AutoXChassis>(new inu::AutoXChassis(*this));
		}


	private:
		bool motorPortsDefined;
		std::shared_ptr<inu::Motor> topleft, topright;
		std::shared_ptr<inu::Motor> bottomleft, bottomright;
	};
}


#endif
