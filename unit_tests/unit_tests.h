#pragma once

// Macro - include library dependency
# define incl_lib(name) __pragma(comment(lib, name))

// State
extern "C" {
	#include "../emulator/State.h"
}

incl_lib("../Debug/emulator.lib")