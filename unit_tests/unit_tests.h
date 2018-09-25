#pragma once

// Macro - include library dependency
# define incl_lib(name) __pragma(comment(lib, name))

extern "C" {
	// State
	#include "../emulator/State.h"

	// Helpers
	#include "../emulator/State_Helpers/State_Helpers.h"

	// Instructions
	#include "../emulator/Instructions/Instructions.h"
}

incl_lib("../Debug/emulator.lib")

extern State8080 *state;