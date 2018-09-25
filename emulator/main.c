#include <stdio.h>

#include "State.h"
#include "Emulator/Emulator.h"
#include "Instructions/Instructions.h"

extern State8080 state;

int main(int argc, char *argv[])
{
	// Initialize
	Init_Memory("../../invaders/invaderstest");

	state.b = 0x00;

	// Fetch/execute instructions
	/*
	Execute_Instruction(Fetch_Next_Instruction());
	printf("%s\n", Fetch_Next_Instruction()->mnemonic);
	printf("a: 0x%02x\n", state.a);

	printf("0x%2x\n", *Get_Mem_Byte(0x1fff));
	printf("0x%2x\n", *Get_Mem_Byte(0x1ffe));

	uint8_t *a = Get_Mem_Byte(0x2000);
	*a = 0x20;

	printf("0x%2x\n", *Get_Mem_Byte(0x2000));
	printf("0x%2x\n", *Get_Mem_Byte(0x4000));
	*/

	getchar();
}