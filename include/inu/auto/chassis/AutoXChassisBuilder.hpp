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
#include "inu/motor/Motor.hpp"
#include "inu/motor/background/SlewMotor.h"

namespace inu {
	class AutoXChassisBuilder : public AutoChassisBuilder {
	public:
		AutoXChassisBuilder() {
			motorPortsDefined = false;
			topleft = topright = nullptr;
			bottomleft = bottomright = nullptr;
		}

		~AutoXChassisBuilder() {
			// No code here; Anything destroyed permeates to built Chassis
			// class
		}


		void SetMotors(int tl, int tr, int bl, int br) {
			topleft = new inu::Motor(std::abs(tl));
			if (tl < 0) topleft->set_reversed(true);

			topright = new inu::Motor(std::abs(tr));
			if (tr < 0) topright->set_reversed(true);

			bottomleft = new inu::Motor(std::abs(bl));
			if (bl < 0) bottomleft->set_reversed(true);

			bottomright = new inu::Motor(std::abs(br));
			if (br < 0) bottomright->set_reversed(true);

			motorPortsDefined = true;
		}

		inu::Motor* GetTopleft() const { return topleft; }

		inu::Motor* GetTopright() const { return topright; }

		inu::Motor* GetBottomleft() const { return bottomleft; }

		inu::Motor* GetBottomright() const { return bottomright; }

		inu::AutoXChassis* Build() {
			if(!motorPortsDefined) {
				return nullptr;
			}

			return new inu::AutoXChassis(this);
		}


	private:
		bool motorPortsDefined;
		inu::Motor *topleft, *topright;
		inu::Motor *bottomleft, *bottomright;
	};
}


#endif
