#include "Instructions.h"
#include "../State.h"
#include "../Helpers/CPU_Helpers.h"

extern State8080 state;

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
	ANI(Get_Instruction_Reg_Val(reg));
}

void ORA(uint8_t reg)
{
	ORI(Get_Instruction_Reg_Val(reg));
}

void XRA(uint8_t reg)
{
	uint8_t valBefore = state.a;
	XRI(Get_Instruction_Reg_Val(reg));

	PSW_Update_Auxiliary_Carry_Bit(state.a, valBefore);
}

void CPI(uint8_t comparedVal)
{
	uint8_t res = state.a - comparedVal;
	PSW_Update_All(res, state.a, 0);
}

void CMP(uint8_t reg)
{
	uint8_t comparedVal = (reg == REG_M)
		? *Get_Register_Pair_Pointer(REG_H)
		: *Get_Register(reg);

	CPI(comparedVal);
}

void CMA()
{
	state.a = ~state.a;
}

// Rotate accumulator left
// * Shift accumulator left
// * LSB = previous MSB
// * CY = previous MSB
void RLC()
{
	uint8_t msb = (state.a & (1 << 7)) >> 7;

	state.a <<= 1;
	state.a |= msb; // Set lsb to previous msb
	state.psw.cy = msb;
}

// Rotate accumulator right
// * Shift accumulator right
// * MSB = previous LSB
// * CY = previous LSB
void RRC()
{
	uint8_t lsb = state.a & 1;

	state.a >>= 1;
	state.a |= (lsb << 7); // Set msb to previous lsb
	state.psw.cy = lsb;
}


// Rotate accumulator left through carry
// * Shift accumulator left
// * LSB = previous CY
// * CY = previous MSB
void RAL()
{
	uint8_t msb = (state.a & (1 << 7)) >> 7;

	state.a <<= 1;
	state.a |= state.psw.cy; // Set lsb to previous cy
	state.psw.cy = msb;
}

// Rotate accumulator right through carry
// * Shift accumulator right
// * MSB = previous CY
// * CY = previous LSB
void RAR()
{
	uint8_t lsb = state.a & 1;

	state.a >>= 1;
	state.a |= (state.psw.cy << 7); // Set msb to previous cy
	state.psw.cy = lsb;
}

void CMC()
{
	state.psw.cy = ~state.psw.cy;
}

void STC()
{
	state.psw.cy = 1;
}