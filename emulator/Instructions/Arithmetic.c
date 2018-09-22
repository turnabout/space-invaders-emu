#include "Instructions.h"
#include "../State.h"

void ADD(uint8_t reg)
{
	uint8_t *accumulator = Get_Reg_Address(REG_A);
	uint8_t *from;

	if (reg == REG_MEMORY)
	{
		// Unimplemented
		return;
	}
	else
	{
		from = Get_Reg_Address(reg);
	}


	*accumulator += *from;

	// Update PSW
	PSW_Update_All(*accumulator, *from, 1);
}

void SUB(uint8_t reg)
{

}