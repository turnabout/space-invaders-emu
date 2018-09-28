#pragma once

// Macro - include library dependency
# define incl_lib(name) __pragma(comment(lib, name))

extern "C" {
	#include <stdio.h> 
	#include <stdlib.h>
	#include <string.h>
	#include "../emulator/CPU/State.h"
	#include "../emulator/Helpers/Number_Helpers.h"
	#include "../emulator/CPU/Helpers/CPU_Helpers.h"
	#include "../emulator/CPU/Instructions/Instructions.h"
	#include "../emulator/Devices/Shift_Register/Shift_Register.h"
	#include "../emulator/Devices/DIP_Switch/DIP_Switch.h"
}

incl_lib("../Debug/emulator.lib")

extern State8080 *state;