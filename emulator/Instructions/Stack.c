#include "Instructions.h"
#include "../State.h"
#include "../State_Helpers/State_Helpers.h"
#include "../Emulator/Emulator.h"

extern State8080 state;

void PUSH(uint8_t reg)
{
	uint8_t *spPointer = Get_Stack_Byte_P(state.sp);
	uint8_t *regPair[2];
		
	Get_Register_Pair(reg, regPair);

	// Store register pair value in stack
	// Example: if DE = 0xddee, (sp-1) = 0xdd; (sp-2) = 0xee;
	*(spPointer - 1) = *regPair[0];
	*(spPointer - 2) = *regPair[1];

	state.sp -= 2;
}

void POP(uint8_t reg)
{
	uint8_t *spPointer = Get_Stack_Byte_P(state.sp);
	uint8_t *regPair[2];
		
	Get_Register_Pair(reg, regPair);

	// Get value that was stored in stack back into the register pair
	*regPair[0] = *(spPointer + 1);
	*regPair[1] = *spPointer;

	state.sp += 2;
}