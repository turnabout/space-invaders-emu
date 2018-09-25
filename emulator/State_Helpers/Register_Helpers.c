#include "State_Helpers.h"
#include "../Emulator/Emulator.h"

extern State8080 state;

uint8_t *Get_Register(uint8_t offset)
{
	if (offset == REG_M)
	{
		// TODO
	}

	uint8_t *adr = (uint8_t *)&state;
	return adr + offset;
}

void Get_Register_Pair(uint8_t reg, uint8_t **regs)
{
	switch (reg)
	{
	case PSW:
		*regs = Get_Register(PSW); // TODO: Use &(state->psw)
		*regs++;
		*regs = Get_Register(REG_A);
		break;

	case REG_B:
		*regs = Get_Register(REG_B);
		*regs++;
		*regs = Get_Register(REG_C);
		break;

	case REG_D:
		*regs = Get_Register(REG_D);
		*regs++;
		*regs = Get_Register(REG_E);
		break;

	case REG_H:
		*regs = Get_Register(REG_H);
		*regs++;
		*regs = Get_Register(REG_L);
		break;
	}
}

uint16_t Get_Register_Pair_Val(uint8_t reg)
{
	uint8_t *pair[2];
	Get_Register_Pair(reg, pair);

	return (*pair[0] << 8) | *pair[1];
}

void Store_Register_Pair_Val(uint8_t reg, uint16_t val)
{
	uint8_t *pair[2];

	Get_Register_Pair(reg, pair);

	// Store most significant byte
	*pair[0] = val >> 8;

	// Store least significant byte
	*pair[1] = val & 0x00ff;
}

uint16_t Get_HL_Address()
{
	return ((uint16_t)state.h << 8) + state.l;
}

uint8_t *Get_HL_Pointer()
{
	return Get_Mem_Byte_P(Get_HL_Address());
}