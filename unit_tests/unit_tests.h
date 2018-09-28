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
}

incl_lib("../Debug/emulator.lib")

extern State8080 *state;