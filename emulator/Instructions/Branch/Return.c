#include "../Instructions.h"
#include "../../State.h"
#include "../../Emulator/Emulator.h"
#include "../../State_Helpers/State_Helpers.h"

extern State8080 state;

void RET()
{
}

void RET_IF(uint8_t cond)
{
	if (cond)
	{
		RET();
	}
}

void RZ()
{
	RET_IF((state.psw.z == 1));
}

void RNZ()
{
	RET_IF((state.psw.z == 0));
}

void RC()
{
	RET_IF((state.psw.cy == 1));
}

void RNC()
{
	RET_IF((state.psw.cy == 0));
}

void RPE()
{
	RET_IF((state.psw.p == 1));
}

void RPO()
{
	RET_IF((state.psw.p == 0));
}

void RM()
{
	RET_IF((state.psw.s == 1));
}

void RP()
{
	RET_IF((state.psw.s == 0));
}