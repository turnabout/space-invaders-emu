#include "Instructions.h"
#include "../State.h"
#include "../Emulator/Emulator.h"
#include "../State_Helpers/State_Helpers.h"

extern State8080 state;

void MVI(uint8_t reg, uint8_t data)
{
	uint8_t *regP = (reg == REG_M)
		? Get_HL_Pointer()
		: Get_Register(reg);

	 *regP = data;
}

void MOV(uint8_t regDst, uint8_t regSrc)
{
	uint8_t *regDstP = (regSrc == REG_M)
		? Get_HL_Pointer()
		: Get_Register(regSrc);

	MVI(regDst, *regDstP);
}