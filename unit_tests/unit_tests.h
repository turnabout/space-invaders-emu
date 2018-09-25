#pragma once

// Macro - include library dependency
# define incl_lib(name) __pragma(comment(lib, name))

extern "C" {
	#include <stdio.h> 
	#include <stdlib.h>
	#include <string.h>
	#include "../emulator/State.h"
	#include "../emulator/State_Helpers/State_Helpers.h"
	#include "../emulator/Instructions/Instructions.h"
	#include "../emulator/Emulator/Emulator.h"
}

incl_lib("../Debug/emulator.lib")

extern State8080 *state;