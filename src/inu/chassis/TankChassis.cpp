#include "inu/chassis/TankChassis.h"
#include "inu/InuException.hpp"
#include "inu/motor/engines/VelocityEngine.h"
#include "inu/motor/engines/VoltageEngine.h"
#include "inu/motor/engines/EncoderEngine.h"
#include "inu/util/Stopwatch.hpp"
#include <cstdint>

using namespace inu;

TankChassis::TankChassis(const TankChassis& chassis) : topleft(chassis.topleft), topright(chassis.topright), bottomleft(chassis.bottomleft), bottomright(chassis.bottomright) {

}

void TankChassis::operator=(const TankChassis& chassis) {
	topleft = chassis.topleft;
	topright = chassis.topright;
	bottomleft = chassis.bottomleft;
	bottomright = chassis.bottomright;
}

TankChassis::TankChassis(inu::port tl, inu::port tr, inu::port bl, inu::port br) : topleft(tl), topright(tr), bottomleft(bl), bottomright(br) {

	encoderSettings.maxVelocity = 10;
}

TankChassis::~TankChassis() {
	topleft.Shutdown();
	topright.Shutdown();
	bottomleft.Shutdown();
	bottomright.Shutdown();
}

void TankChassis::Swerve(int forward, int turn, int maxVelocity) {
	forward = std::clamp<int>(forward, -maxVelocity, maxVelocity);
	turn = std::clamp<int>(turn, -maxVelocity, maxVelocity);

	auto tl = std::clamp<int>(forward + turn, -maxVelocity, maxVelocity);
	auto bl = std::clamp<int>(forward + turn,-maxVelocity, maxVelocity);
	auto tr = std::clamp<int>(-forward + turn,-maxVelocity, maxVelocity);
	auto br = std::clamp<int>(-forward + turn,-maxVelocity, maxVelocity);

	ChangeEngine<engine::VelocityEngine>();

	topleft.SetTarget(tl);
	topright.SetTarget(tr);
	bottomleft.SetTarget(bl);
	bottomright.SetTarget(br);

	Execute();
}

void TankChassis::RawSwerve(int forward, int turn) {
	forward = std::clamp<int>(forward, -127, 127);
	turn = std::clamp<int>(turn, -127, 127);

	auto tl = std::clamp<int>(forward + turn, -127, 127);
	auto bl = std::clamp<int>(forward + turn, -127, 127);
	auto tr = std::clamp<int>(-forward + turn, -127, 127);
	auto br = std::clamp<int>(-forward + turn, -127, 127);

	ChangeEngine<engine::VoltageEngine>();

	topleft.SetTarget(tl);
	topright.SetTarget(tr);
	bottomleft.SetTarget(bl);
	bottomright.SetTarget(br);

	Execute();
}


void TankChassis::Turn(double ticks) {
	ChangeEngine<engine::EncoderEngine>(engine::EncoderEngine::RELATIVE, encoderSettings);

	topleft.SetTarget(ticks);
	topright.SetTarget(ticks);
	bottomleft.SetTarget(ticks);
	bottomright.SetTarget(ticks);

	Execute();

	WaitForEncoders(1);
}

void TankChassis::Forward(double ticks) {
	ChangeEngine<engine::EncoderEngine>(engine::EncoderEngine::RELATIVE, encoderSettings);

	topleft.SetTarget(ticks);
	topright.SetTarget(-ticks);
	bottomleft.SetTarget(ticks);
	bottomright.SetTarget(-ticks);

	Execute();

	WaitForEncoders(1);
}

void TankChassis::Backward(double ticks) {
	Forward(-ticks);
}

void TankChassis::WaitForEncoders(double steadyWait) {
	inu::Stopwatch inSteady;
	bool steady = false;

	auto tl = topleft.GetEngine<engine::EncoderEngine>().lock();
	auto tr = topright.GetEngine<engine::EncoderEngine>().lock();
	auto br = bottomright.GetEngine<engine::EncoderEngine>().lock();
	auto bl = bottomleft.GetEngine<engine::EncoderEngine>().lock();

	while (true) {
		if(tl->IsFinished() && tr->IsFinished() &&
			bl->IsFinished() && br->IsFinished() && !steady) {

			steady = true;
			inSteady.Mark();
		}

		if(steady) {
			if(inSteady.GetElapsed() > steadyWait * 1000) {
				break;
			}
		}

		pros::delay(10);
	}
}


void TankChassis::Stop() {
	topleft.Shutdown();
	topright.Shutdown();
	bottomleft.Shutdown();
	bottomright.Shutdown();
}

void TankChassis::Execute() {
	topleft.Execute();
	topright.Execute();
	bottomleft.Execute();
	bottomright.Execute();
}
