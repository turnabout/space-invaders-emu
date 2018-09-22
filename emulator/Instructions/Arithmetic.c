#include "Instructions.h"
#include "../State.h"

void ADD(uint8_t reg)
{
	uint8_t *accumulator = Get_Reg_Address(REG_A);
	uint8_t *from = Get_Reg_Address(reg);

	*accumulator += *from;

	// Update PSW
	PSW_Update_Sign_Bit(*accumulator);
}

void SUB(uint8_t reg)
{

}