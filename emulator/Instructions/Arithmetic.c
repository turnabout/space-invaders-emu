#include "Instructions.h"
#include "../State.h"

// Do an arithmetic operation on Accumulator
// val: Value to apply
// isAddition: Whether operation is an addition
void DO_ARITHMETIC(uint8_t val, uint8_t isAddition)
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

	DO_ARITHMETIC(*Get_Reg_Address(reg), 1);
}

void SUB(uint8_t reg)
{
	if (reg == REG_MEMORY) // TODO
	{
		return;
	}

	DO_ARITHMETIC(*Get_Reg_Address(reg), 0);
}