#include "../Instructions.h"
#include "../../State.h"

extern State8080 state;

void CALL(uint8_t hi, uint8_t lo)
{
}

void CALL_IF(uint8_t cond, uint8_t hi, uint8_t lo)
{
	if (cond)
	{
		CALL(hi, lo);
	}
}

void CZ(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.z == 1), hi, lo);
}

void CNZ(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.z == 0), hi, lo);
}

void CC(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.cy == 1), hi, lo);
}

void CNC(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.cy == 0), hi, lo);
}

void CPE(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.p == 1), hi, lo);
}

void CPO(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.p == 0), hi, lo);
}

void CM(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.s == 1), hi, lo);
}

void CP(uint8_t hi, uint8_t lo)
{
	CALL_IF((state.psw.s == 0), hi, lo);
}