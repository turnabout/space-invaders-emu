#include <stdlib.h>
#include <stdio.h>

#include "Instructions.h"
#include "../State.h"
#include "../CPU.h"

extern State8080 state;
extern API8080 externalFuncs;

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
	exit(1);
}

void IN(uint8_t portN)
{
	state.a = externalFuncs.readInputPort(portN);
}

void OUT(uint8_t portN)
{
	externalFuncs.writeInputPort(portN, state.a);
}

void RST(uint8_t pos)
{
	uint16_t val = (uint16_t)(pos * 0x08);
	CALL(val >> 8, val & 0xff);
	/*
		ISRs
		0  - 7  0x0000 - 0x0007 RST0
		8  - 15 0x0008 - 0x000f RST1
		16 - 23 0x0010 - 0x0017 etc.
		24 - 31 0x0018 - 0x001f
		32 - 39 0x0020 - 0x0027
		40 - 47 0x0028 - 0x002f
		48 - 55 0x0030 - 0x0037
		56 - 63 0x0038 - 0x003f
	*/
}

void NOT_IMPLEMENTED()
{
	printf("NOT_IMPLEMENTED\n");
}