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
		// TODO
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

void PSW_Update_Parity_Bit(uint8_t opRes)
{
	// XOR all bits together then invert; if result is 1, bits are even.
	opRes ^= opRes >> 4;
	opRes ^= opRes >> 2;
	opRes ^= opRes >> 1;

	state.psw.p = (~opRes) & 1
		? 1
		: 0;
}

void PSW_Update_Carry_Bit(uint8_t opRes, uint8_t operand, uint8_t valIfOverflow)
{
	state.psw.cy = (opRes < operand)
		? valIfOverflow
		: ~valIfOverflow;
}

void PSW_Update_All(uint8_t opRes, uint8_t operand, uint8_t valIfOverflow)
{
	PSW_Update_Zero_Bit(opRes);
	PSW_Update_Sign_Bit(opRes);
	PSW_Update_Parity_Bit(opRes);
	PSW_Update_Carry_Bit(opRes, operand, valIfOverflow);
}

void Get_Register_Pair(uint8_t reg, uint8_t **regs)
{
	switch (reg)
	{
	case PSW:
		*regs = Get_Reg_Address(PSW);
		*regs++;
		*regs = Get_Reg_Address(REG_A);
		break;

	case REG_B:
		*regs = Get_Reg_Address(REG_B);
		*regs++;
		*regs = Get_Reg_Address(REG_C);
		break;

	case REG_D:
		*regs = Get_Reg_Address(REG_D);
		*regs++;
		*regs = Get_Reg_Address(REG_E);
		break;

	case REG_H:
		*regs = Get_Reg_Address(REG_H);
		*regs++;
		*regs = Get_Reg_Address(REG_L);
		break;
	}
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