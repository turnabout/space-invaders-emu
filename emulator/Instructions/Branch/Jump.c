#include "../Instructions.h"
#include "../../State.h"
#include "../../Helpers/Number_Helpers.h"

extern State8080 state;

void JMP(uint8_t hi, uint8_t lo)
{
	state.pc = Bytes_To_Short(hi, lo);
}

void JMP_IF(uint8_t cond, uint8_t hi, uint8_t lo)
{
	if (cond)
	{
		JMP(hi, lo);
	}
}

void JZ(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.z == 1), hi, lo);
}

void JNZ(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.z == 0), hi, lo);
}

void JC(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.cy == 1), hi, lo);
}

void JNC(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.cy == 0), hi, lo);
}

void JPE(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.p == 1), hi, lo);
}

void JPO(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.p == 0), hi, lo);
}

void JM(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.s == 1), hi, lo);
}

void JP(uint8_t hi, uint8_t lo)
{
	JMP_IF((state.psw.s == 0), hi, lo);
}