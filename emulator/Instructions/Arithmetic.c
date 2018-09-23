#include "Instructions.h"
#include "../State.h"

// Do an arithmetic operation on Accumulator
// val: Value to apply
// isAddition: Whether operation is an addition
// carry: Include carry in arithmetic. 0 to ignore
// Return: Result of the operation
void Do_Arithmetic(uint8_t val, uint8_t isAddition)
{
	uint8_t *accumulator = Get_Reg_Address(REG_A);
	uint8_t ogAccumVal = *accumulator;

	*accumulator += (isAddition) ? val : -val;

	// Update PSW
	PSW_Update_All(*accumulator, ogAccumVal, isAddition);
}

void ADD(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic(*Get_Reg_Address(reg), 1);
}

void ADC(uint8_t reg)
{
	State8080 *state = Get_State();

	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	// Store carry value
	uint8_t cy = state->psw.cy;
	state->psw.cy = 0;

	Do_Arithmetic(*Get_Reg_Address(reg), 1);

	// Add previously stored carry, if necessary
	if (cy)
	{
		uint8_t *regA = Get_Reg_Address(REG_A);

		*regA += cy;

		/*
		 * Detect whether carry caused overflow.
		 * If carry caused overflow, set cy to 1.
		 */
		if (*regA == 0)
		{
			state->psw.cy = 1;
		}
	}
}

void SUB(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	Do_Arithmetic(*Get_Reg_Address(reg), 0);
}