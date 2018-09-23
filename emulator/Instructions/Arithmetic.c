#include "Instructions.h"
#include "../State.h"

// Do an arithmetic operation on Accumulator
// val: Value to apply
// isAddition: Whether operation is an addition
// carry: Include carry in arithmetic. 0 to ignore
// Return: Result of the operation
void Do_Arithmetic(uint8_t val, uint8_t isAddition)
{
	uint8_t *accumulator = Get_Register(REG_A);
	uint8_t ogAccumVal = *accumulator;

	*accumulator += (isAddition) ? val : -val;

	// Update PSW
	PSW_Update_All(*accumulator, ogAccumVal, isAddition);
}

// Do an arithmetic operation on Accumulator with carry or borrow
void Do_Arithmetic_With_CB(uint8_t val, uint8_t isAddition)
{
	State8080 *state = Get_State();
	uint8_t cy = state->psw.cy;

	Do_Arithmetic(val, isAddition);

	// Add/subtract previously stored carry
	if (cy)
	{
		uint8_t *acc = Get_Register(REG_A);
		*acc += (isAddition) ? cy : -cy;
	
		// If carry/borrow caused out of bounds, set the carry bit
		if (*acc == ((isAddition) ? 0 : 255))
		{
			state->psw.cy = 1;
		}
	}
}

void ADD(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic(*Get_Register(reg), 1);
}

void ADC(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic_With_CB(*Get_Register(reg), 1);
}

void SUB(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic(*Get_Register(reg), 0);
}

void SBB(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic_With_CB(*Get_Register(reg), 0);
}

void INR(uint8_t reg)
{
	uint8_t *regP = Get_Register(reg);
	*regP += 1;

	// Does not update carry
	PSW_Update_Zero_Bit(*regP);
	PSW_Update_Sign_Bit(*regP);
	PSW_Update_Parity_Bit(*regP);
}

void DCR(uint8_t reg)
{
	uint8_t *regP = Get_Register(reg);
	*regP -= 1;

	// Does not update carry
	PSW_Update_Zero_Bit(*regP);
	PSW_Update_Sign_Bit(*regP);
	PSW_Update_Parity_Bit(*regP);
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