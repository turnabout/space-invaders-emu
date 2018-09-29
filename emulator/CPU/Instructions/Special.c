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
		0  - 7
		8  - 15
		16 - 23
		24 - 31
		32 - 39
		40 - 47
		48 - 55
		56 - 63
	*/
}

void NOT_IMPLEMENTED()
{
	printf("NOT_IMPLEMENTED\n");
}