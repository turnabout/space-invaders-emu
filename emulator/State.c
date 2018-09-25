#include "State.h"

// Emulator's global state holding registers, PSW, etc.
State8080 state = {
	0x00, // Accumulator
	0x00, // Other Registers (b-c-d-e-h-l)
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	{0, 0, 0, 0, 0}, // PSW (Zero, Sign, Parity, Carry, Aux Carry)
	1,   // Interrupt
	0x0, // Stack pointer
	0x0  // Program counter
};

#ifdef _DEBUG
State8080 *Get_State()
{
	return &state;
}

void Reset_State()
{
	state.a = 0x00;
	state.b = 0x00;
	state.c = 0x00;
	state.d = 0x00;
	state.e = 0x00;
	state.h = 0x00;
	state.l = 0x00;
	state.int_enable = 1;
	state.sp = 0x00;
	state.pc = 0x0;

	state.psw.z = 0;
	state.psw.s = 0;
	state.psw.p = 0;
	state.psw.cy = 0;
	state.psw.ac = 0;
}
#endif