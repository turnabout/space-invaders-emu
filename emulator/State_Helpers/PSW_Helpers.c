#include "State_Helpers.h"

extern State8080 state;

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

void PSW_Update_Carry_Bit(uint8_t opRes, uint8_t operand1, uint8_t isAddition)
{
	// Addition: carry flag is set if the operation result is smaller than
	// the first operand's value.
	if (isAddition)
	{
		state.psw.cy = (opRes < operand1) ? 1 : 0;
		return;
	}

	// Subtraction: carry flag is set if the operand 2 is greater than operand 1
	// operand2 = operand1 - result
	state.psw.cy = ((uint8_t)(operand1 - opRes) > operand1) ? 1 : 0;
}

void PSW_Update_Carry_Bit_16(uint16_t opRes, uint16_t operand1, uint8_t isAddition)
{
	if (isAddition)
	{
		state.psw.cy = (opRes < operand1) ? 1 : 0;
		return;
	}

	state.psw.cy = ((uint16_t)(operand1 - opRes) > operand1) ? 1 : 0;
}

void PSW_Update_All(uint8_t opRes, uint8_t operand, uint8_t valIfOverflow)
{
	PSW_Update_Zero_Bit(opRes);
	PSW_Update_Sign_Bit(opRes);
	PSW_Update_Parity_Bit(opRes);
	PSW_Update_Carry_Bit(opRes, operand, valIfOverflow);
}