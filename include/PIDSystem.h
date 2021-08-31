#ifndef PIDSYSTEM_H
#define PIDSYSTEM_H


#include "main.h"
#include <map>

struct PIDMotor;

class PIDSystem {
public:
	static void Start();

	static void SetDelay();

	static void EnrollMotor(PIDMotor* motor);

	static void RemoveMotor(PIDMotor* motor);

	static bool IsRunning();

	static void Stop();
private:
	static void PIDTask(void* parameters);



private:
	static pros::Task* PIDtask;

	static std::map<unsigned int, PIDMotor*> motorMap;

	static unsigned int delay;
	static bool running;
};






#endif
