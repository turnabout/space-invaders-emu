#include "State.h"

// Emulator's global state holding registers, PSW, etc.
static struct State8080 state = {
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
	0x0, // Program counter
	0x0  // Address pointed at by registers h/l
};

uint8_t *Get_Reg_Address(uint8_t offset)
{
	if (offset == REG_MEMORY)
	{
		// Unimplemented
	}

	uint8_t *adr = (uint8_t *)&state;
	return adr + offset;
}

void PSW_Update_Zero_Bit(uint8_t opRes)
{
	state.psw.z = (opRes == 0)
		? 1
		: 0;
}

void PSW_Update_Sign_Bit(uint8_t opRes)
{
	state.psw.s = (opRes & 0b10000000)
		? 1 
		: 0;
}

State8080 *Get_State()
{
	return &state;
}

#ifdef _DEBUG
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
	state.memory = 0x0;

	state.psw.z = 0;
	state.psw.s = 0;
	state.psw.p = 0;
	state.psw.cy = 0;
	state.psw.ac = 0;
}
#endif