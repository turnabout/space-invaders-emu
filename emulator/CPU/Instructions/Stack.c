#include "Instructions.h"
#include "../State.h"
#include "../CPU.h"
#include "../Helpers/CPU_Helpers.h"

extern State8080 state;
extern API8080 externalFuncs;

void Push_Value_On_Stack(uint8_t hi, uint8_t lo)
{
	uint8_t *spPointer = externalFuncs.accessMem(state.sp);

	*(spPointer - 1) = hi;
	*(spPointer - 2) = lo;

	state.sp -= 2;
}

void Pull_Value_From_Stack(uint8_t *hi, uint8_t *lo)
{
	uint8_t *spPointer = externalFuncs.accessMem(state.sp);

	*hi = *(spPointer + 1);
	*lo = *spPointer;

	state.sp += 2;
}

void PUSH(uint8_t reg)
{
	uint8_t *regPair[2];
	Get_Register_Pair(reg, regPair);

	Push_Value_On_Stack(*regPair[0], *regPair[1]);
}

void POP(uint8_t reg)
{
	uint8_t *regPair[2];

	Get_Register_Pair(reg, regPair);
	Pull_Value_From_Stack(regPair[0], regPair[1]);
}

void SPHL()
{
	state.sp = Get_Register_Pair_Val(REG_H);
}

void XTHL()
{
	uint8_t *spPointer = externalFuncs.accessMem(state.sp);
	uint8_t *hl[2];
	uint8_t temp[2];
		
	Get_Register_Pair(REG_H, hl);

	// Temp H
	temp[0] = *hl[0];

	// Temp L
	temp[1] = *hl[1];

	// Transfer from stack to HL
	*hl[0] = *(spPointer + 1);  // H
	*hl[1] = *spPointer;        // L

	// Transfer from HL temp to stack
	*(spPointer + 1) = temp[0]; // H
	*spPointer = temp[1];       // L
}