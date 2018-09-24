#include "Instructions.h"
#include "../State.h"

extern struct State8080 state;

// Set PSW from a bitwise operation result
void Set_PSW_Bitwise_Op(uint8_t result)
{
	PSW_Update_Zero_Bit(state.a);
	PSW_Update_Sign_Bit(state.a);
	PSW_Update_Parity_Bit(state.a);

	// All bitwise operations reset carry bit
	state.psw.cy = 0;
}

void ANI(uint8_t val)
{
	state.a &= val;
	Set_PSW_Bitwise_Op(state.a);
}

void ORI(uint8_t val)
{
	state.a |= val;
	Set_PSW_Bitwise_Op(state.a);
}

void XRI(uint8_t val)
{
	state.a ^= val;
	Set_PSW_Bitwise_Op(state.a);
}

void ANA(uint8_t reg)
{
	ANI(*Get_Register(reg));
}

void ORA(uint8_t reg)
{
	ORI(*Get_Register(reg));
}

void XRA(uint8_t reg)
{
	XRI(*Get_Register(reg));
}

void CMP(uint8_t reg)
{
	uint8_t res = state.a - *Get_Register(reg);
	PSW_Update_All(res, state.a, 0);
}

void CMA()
{
	state.a = ~state.a;
}

void RLC()
{
}

void RRC()
{
}

void RAL()
{
}

void RAR()
{
}

void CMC()
{
	state.psw.cy = ~state.psw.cy;
}

void STC()
{
	state.psw.cy = 1;
}