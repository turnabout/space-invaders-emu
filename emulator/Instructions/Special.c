#include "Instructions.h"
#include "../State.h"

extern State8080 state;

void EI()
{
	state.int_enable = 1;
}

void DI()
{
	state.int_enable = 0;
}

void NOP()
{
}

void HLT()
{
}

void IN(uint8_t deviceN)
{
}

void OUT(uint8_t deviceN)
{
}

void RST(uint8_t pos)
{
}

void NOT_IMPLEMENTED()
{
}