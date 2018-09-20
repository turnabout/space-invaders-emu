#include "State.h"

// Current global state of registers, PSW, etc.
static struct State8080 state = {
	0x1a, // Accumulator
	0x2b, // Other Registers (b-c-d-e-h-l)
	0x3c,
	0x4d,
	0x5e,
	0x66,
	0x77,
	{0, 0, 0, 0, 0}, // PSW (Zero, Sign, Parity, Carry, Aux Carry)
	1,   // Interrupt
	0,   // Stack pointer
	0x0, // Program counter
	0    // Address pointed at by registers h/l
};

uint8_t *Get_Reg_Address(uint8_t offset)
{
	if (offset == REG_M)
	{
		// Unimplemented
	}

	uint8_t *adr = (uint8_t *)&state;
	return adr + offset;
}

void PSW_Update_Sign_Bit(uint8_t opRes)
{
	state.psw.s = (opRes | 0b10000000)
		? 1 
		: 0;
}