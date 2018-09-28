#include "Instructions.h"
#include "../State.h"
#include "../CPU.h"
#include "../Helpers/CPU_Helpers.h"
#include "../../Helpers/Number_Helpers.h"

extern State8080 state;
extern API8080 externalFuncs;

void MVI(uint8_t reg, uint8_t data)
{
	uint8_t *regP = (reg == REG_M)
		? Get_Register_Pair_Pointer(REG_H)
		: Get_Register(reg);

	 *regP = data;
}

void MOV(uint8_t regDst, uint8_t regSrc)
{
	uint8_t *regDstP = (regSrc == REG_M)
		? Get_Register_Pair_Pointer(REG_H)
		: Get_Register(regSrc);

	MVI(regDst, *regDstP);
}

void LXI(uint8_t reg, uint8_t hi, uint8_t lo)
{
	if (reg == SP)
	{
		state.sp = Bytes_To_Short(hi, lo);
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

void SHLD(uint8_t hi, uint8_t lo)
{
	uint8_t *adr = externalFuncs.accessMem(Bytes_To_Short(hi, lo));

	*(adr + 1) = state.h;
	*adr = state.l;
}

void LHLD(uint8_t hi, uint8_t lo)
{
	uint8_t *adr = externalFuncs.accessMem(Bytes_To_Short(hi, lo));

	state.h = *(adr + 1);
	state.l = *adr;
}

void PCHL()
{
	state.pc = Bytes_To_Short(state.h, state.l);
}

void XCHG()
{
	uint8_t *hl[2], *de[2];
	uint8_t temp[2];
		
	Get_Register_Pair(REG_H, hl);
	Get_Register_Pair(REG_D, de);

	temp[0] = *hl[0];
	temp[1] = *hl[1];

	*hl[0] = *de[0];
	*hl[1] = *de[1];

	*de[0] = temp[0];
	*de[1] = temp[1];
}

void STA(uint8_t hi, uint8_t lo)
{
	uint8_t *dst = externalFuncs.accessMem(
		Bytes_To_Short(hi, lo)
	);

	*dst = state.a;
}

void LDA(uint8_t hi, uint8_t lo)
{
	uint8_t *src = externalFuncs.accessMem(
		Bytes_To_Short(hi, lo)
	);

	state.a = *src;
}