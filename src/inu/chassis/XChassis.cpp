#include "inu/chassis/XChassis.h"
#include "inu/InuException.hpp"
#include "inu/motor/engines/VelocityEngine.h"
#include "inu/motor/engines/VoltageEngine.h"
#include "inu/motor/engines/EncoderEngine.h"
#include "inu/util/VectorMath.hpp"
#include "inu/util/Stopwatch.hpp"
#include <cstdint>

using namespace inu;

XChassis::XChassis(const XChassis& chassis) : topleft(chassis.topleft), topright(chassis.topright), bottomleft(chassis.bottomleft), bottomright(chassis.bottomright) {

}

void XChassis::operator=(const XChassis& chassis) {
	topleft = chassis.topleft;
	topright = chassis.topright;
	bottomleft = chassis.bottomleft;
	bottomright = chassis.bottomright;
}

XChassis::XChassis(inu::port tl, inu::port tr, inu::port bl, inu::port br) : topleft(tl), topright(tr), bottomleft(bl), bottomright(br) {

	encoderSettings.maxVelocity = 10;
}

XChassis::~XChassis() {
	topleft.Shutdown();
	topright.Shutdown();
	bottomleft.Shutdown();
	bottomright.Shutdown();
}

void XChassis::Swerve(int forward, int right, int turn, int maxVelocity) {
	forward = std::clamp<int>(forward, -maxVelocity, maxVelocity);
	right = std::clamp<int>(right, -maxVelocity, maxVelocity);
	turn = std::clamp<int>(turn, -maxVelocity, maxVelocity);

	auto tl = std::clamp<int>(forward + turn + right, -maxVelocity, maxVelocity);
	auto bl = std::clamp<int>(forward + turn - right, -maxVelocity, maxVelocity);
	auto tr = std::clamp<int>(-forward + turn + right, -maxVelocity, maxVelocity);
	auto br = std::clamp<int>(-forward + turn - right, -maxVelocity, maxVelocity);

	ChangeEngine<engine::VelocityEngine>();

	topleft.SetTarget(tl);
	topright.SetTarget(tr);
	bottomleft.SetTarget(bl);
	bottomright.SetTarget(br);

	Execute();
}

void XChassis::RawSwerve(int forward, int right, int turn) {
	forward = std::clamp<int>(forward, -127, 127);
	right = std::clamp<int>(right, -127, 127);
	turn = std::clamp<int>(turn, -127, 127);

	auto tl = std::clamp<int>(forward + turn + right, -127, 127);
	auto bl = std::clamp<int>(forward + turn - right, -127, 127);
	auto tr = std::clamp<int>(-forward + turn + right, -127, 127);
	auto br = std::clamp<int>(-forward + turn - right, -127, 127);

	ChangeEngine<engine::VoltageEngine>();

	topleft.SetTarget(tl);
	topright.SetTarget(tr);
	bottomleft.SetTarget(bl);
	bottomright.SetTarget(br);

	Execute();
}


void XChassis::VectorPush(int magnitude, int turn, Vector robotVector, Vector targetVector) {

	Vector rel = VectorMath::RelativeVector(robotVector, targetVector);
	rel = rel.Normalize();
	RawSwerve(rel.y * magnitude, rel.x * magnitude, turn);
}


void XChassis::Turn(double ticks) {
	ChangeEngine<engine::EncoderEngine>(engine::EncoderEngine::RELATIVE, encoderSettings);

	topleft.SetTarget(ticks);
	topright.SetTarget(ticks);
	bottomleft.SetTarget(ticks);
	bottomright.SetTarget(ticks);

	Execute();

	WaitForEncoders(1);
}

void XChassis::Forward(double ticks) {
	ChangeEngine<engine::EncoderEngine>(engine::EncoderEngine::RELATIVE, encoderSettings);

	topleft.SetTarget(ticks);
	topright.SetTarget(-ticks);
	bottomleft.SetTarget(ticks);
	bottomright.SetTarget(-ticks);

	Execute();

	WaitForEncoders(1);
}

void XChassis::Backward(double ticks) {
	Forward(-ticks);
}


void XChassis::StrafeRight(double ticks) {
	ChangeEngine<engine::EncoderEngine>(engine::EncoderEngine::RELATIVE, encoderSettings);

	topleft.SetTarget(ticks);
	topright.SetTarget(ticks);
	bottomleft.SetTarget(-ticks);
	bottomright.SetTarget(-ticks);

	Execute();

	WaitForEncoders(1);
}

void XChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

void XChassis::WaitForEncoders(double steadyWait) {
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


void XChassis::Stop() {
	topleft.Shutdown();
	topright.Shutdown();
	bottomleft.Shutdown();
	bottomright.Shutdown();
}

void XChassis::Execute() {
	topleft.Execute();
	topright.Execute();
	bottomleft.Execute();
	bottomright.Execute();
}
