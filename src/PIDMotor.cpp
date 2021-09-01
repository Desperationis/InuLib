#include "PIDMotor.h"
#include "PIDSystem.h"

using namespace pros;

PIDMotor::PIDMotor(unsigned int port) {
	this->port = port;
	PIDSystem::EnrollMotor(this);
}

PIDMotor::~PIDMotor() {
	PIDSystem::RemoveMotor(this);
}

void PIDMotor::Set(unsigned int target) {
	this->target = target;
}


void PIDMotor::SetP(float p) {
	this->p = p;
}


void PIDMotor::SetI(float i) {
	this->i = i;
}


void PIDMotor::SetD(float d) {
	this->d = d;
}

unsigned int PIDMotor::GetPort() {
	return port;
}

unsigned int PIDMotor::GetTarget() {
	return target;
}

float PIDMotor::GetP() {
	return p;
}

float PIDMotor::GetI() {
	return i;
}

float PIDMotor::GetD() {
	return d;
}









