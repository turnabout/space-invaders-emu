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

void LXI(uint8_t reg, uint8_t hi, uint8_t lo)
{
	if (reg == SP)
	{
		state.sp = (uint16_t)(hi << 8) + lo;
		return;
	}

	uint8_t *pair[2];

	Get_Register_Pair(reg, pair);

	*pair[0] = hi;
	*pair[1] = lo;
}

void STAX(uint8_t reg)
{
	uint8_t *adr = Get_Register_Pair_Pointer(reg);
	*adr = state.a;
}

void LDAX(uint8_t reg)
{
	state.a = *Get_Register_Pair_Pointer(reg);
}