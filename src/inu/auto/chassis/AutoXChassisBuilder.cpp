#include "inu/auto/chassis/AutoXChassisBuilder.h"
#include "inu/auto/chassis/AutoXChassis.h"

using namespace inu;

AutoXChassisBuilder::AutoXChassisBuilder() {
	motorPortsDefined = false;
}

AutoXChassisBuilder::~AutoXChassisBuilder() {
	topleft.reset();
	topright.reset();
	bottomleft.reset();
	bottomright.reset();
}


void AutoXChassisBuilder::SetMotors(inu::port tl, inu::port tr, inu::port bl, inu::port br) {

	//TODO THROW EXCEPTION HERE

	topleft.reset(new inu::Motor(tl));

	topright.reset(new inu::Motor(tr));

	bottomleft.reset(new inu::Motor(bl));

	bottomright.reset(new inu::Motor(br));

	motorPortsDefined = true;
}

std::weak_ptr<inu::Motor> AutoXChassisBuilder::GetTopleft() const { 
	return topleft; 
}

std::weak_ptr<inu::Motor> AutoXChassisBuilder::GetTopright() const {
	return topright; 
}

std::weak_ptr<inu::Motor> AutoXChassisBuilder::GetBottomleft() const { 
	return bottomleft; 
}

std::weak_ptr<inu::Motor> AutoXChassisBuilder::GetBottomright() const { 
	return bottomright; 
}

std::shared_ptr<inu::AutoXChassis> AutoXChassisBuilder::Build() {
	// TODO THROW EXCEPTION HERE
	if(!motorPortsDefined) {
		return nullptr;
	}

	return std::shared_ptr<inu::AutoXChassis>(new inu::AutoXChassis(*this));
}
