#include "Instructions.h"
#include "../State.h"
#include "../Helpers/CPU_Helpers.h"

extern State8080 state;

// Do an arithmetic operation on Accumulator
// val: Value to apply
// isAddition: Whether operation is an addition
// carry: Include carry in arithmetic. 0 to ignore
// Return: Result of the operation
void Do_Arithmetic(uint8_t val, uint8_t isAddition)
{
	uint8_t ogAccumVal = state.a;

	state.a += (isAddition) ? val : -val;

	// Update PSW
	PSW_Update_All(state.a, ogAccumVal, isAddition);
}

// Do an arithmetic operation on Accumulator with carry or borrow
void Do_Arithmetic_With_CB(uint8_t val, uint8_t isAddition)
{
	uint8_t cy = state.psw.cy;

	Do_Arithmetic(val, isAddition);

	// Add/subtract previously stored carry
	if (cy)
	{
		state.a += (isAddition) ? cy : -cy;
	
		// If carry/borrow caused out of bounds, set the carry bit
		if (state.a == ((isAddition) ? 0 : 255))
		{
			state.psw.cy = 1;
		}
	}
}

void ADD(uint8_t reg)
{
	Do_Arithmetic(
		Get_Instruction_Reg_Val(reg), 
		1
	);
}

void ADC(uint8_t reg)
{
	Do_Arithmetic_With_CB(
		Get_Instruction_Reg_Val(reg), 
		1
	);
}

void SUB(uint8_t reg)
{
	Do_Arithmetic(
		Get_Instruction_Reg_Val(reg), 
		0
	);
}

void SBB(uint8_t reg)
{
	Do_Arithmetic_With_CB(
		Get_Instruction_Reg_Val(reg),
		0
	);
}

void INR(uint8_t reg)
{
	uint8_t *regP = (reg == REG_M)
		? Get_Register_Pair_Pointer(REG_H)
		: Get_Register(reg);
	uint8_t valBefore = *regP;

	*regP += 1;

	// Does not update normal carry
	PSW_Update_Zero_Bit(*regP);
	PSW_Update_Sign_Bit(*regP);
	PSW_Update_Parity_Bit(*regP);
	PSW_Update_Auxiliary_Carry_Bit(*regP, valBefore);
}

void DCR(uint8_t reg)
{
	uint8_t *regP = (reg == REG_M)
		? Get_Register_Pair_Pointer(REG_H)
		: Get_Register(reg);
	uint8_t valBefore = *regP;

	*regP -= 1;

	// Does not update carry
	PSW_Update_Zero_Bit(*regP);
	PSW_Update_Sign_Bit(*regP);
	PSW_Update_Parity_Bit(*regP);
	PSW_Update_Auxiliary_Carry_Bit(*regP, valBefore);
}

void ADI(uint8_t val)
{
	Do_Arithmetic(val, 1);
}

void ACI(uint8_t val)
{
	Do_Arithmetic_With_CB(val, 1);
}

void SUI(uint8_t val)
{
	Do_Arithmetic(val, 0);
}

void SBI(uint8_t val)
{
	Do_Arithmetic_With_CB(val, 0);
}

void INX(uint8_t reg)
{
	// Increment SP
	if (reg == SP)
	{
		state.sp += 1;
		return;
	}

	// Increment register pair
	uint16_t regPairVal = Get_Register_Pair_Val(reg);

	regPairVal += 1;

	Store_Register_Pair_Val(reg, regPairVal);
}

void DCX(uint8_t reg)
{
	// Decrement SP
	if (reg == SP)
	{
		state.sp -= 1;
		return;
	}

	// Decrement register pair
	uint16_t regPairVal = Get_Register_Pair_Val(reg);

	regPairVal -= 1;

	Store_Register_Pair_Val(reg, regPairVal);
}

void DAD(uint8_t reg)
{
	uint16_t hlVal = Get_Register_Pair_Val(REG_H);

	uint16_t addedVal = (reg == SP)
		? state.sp
		: Get_Register_Pair_Val(reg);

	Store_Register_Pair_Val(REG_H, hlVal + addedVal);
	PSW_Update_Carry_Bit_16(hlVal + addedVal, hlVal, 1);
}

void DAA()
{
	uint8_t startVal = state.a;

	// Adjust 4 LSB
	if ((state.a & 0x0f) > 9 || state.psw.ac == 1)
	{
		state.a += 6;
	}
	PSW_Update_Auxiliary_Carry_Bit(state.a, startVal);
	startVal = state.a;

	// Adjust 4 MSB
	if ((state.a >> 4) > 9 || state.psw.cy == 1)
	{
		state.a += 0b01100000; // Add 6 to 4 MSB
	}
	PSW_Update_Carry_Bit(state.a, startVal, 1);

	// Update other PSW bits with final result
	PSW_Update_Zero_Bit(state.a);
	PSW_Update_Sign_Bit(state.a);
	PSW_Update_Parity_Bit(state.a);
}