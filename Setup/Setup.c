#pragma systemFile
#ifndef SETUP_SOURCE
#define SETUP_SOURCE

#include "Helpers/Helpers.h"
#include "Controllers/Slew/Slew.h"
#include "Controllers/PID/PID.h"
#include "Setup.h"


void InitCustomLibrary() {
	ResetEncoders();
	InitPID();
	InitSlew();
}


#endif
