#include "CPU_Helpers.h"
#include "../../Helpers/Number_Helpers.h"
#include "../CPU.h"

extern State8080 state;
extern API8080 externalFuncs;

uint8_t *Get_Register(uint8_t offset)
{
	uint8_t *adr = (uint8_t *)&state;
	return adr + offset;
}

void Get_Register_Pair(uint8_t reg, uint8_t **regs)
{
	switch (reg)
	{
	case PSW:
		*regs = Get_Register(PSW);
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

	return Bytes_To_Short(*pair[0], *pair[1]);
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

uint8_t *Get_Register_Pair_Pointer(uint8_t reg)
{
	return externalFuncs.accessMem(Get_Register_Pair_Val(reg));
}