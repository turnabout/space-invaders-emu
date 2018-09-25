#include <stdio.h>

#include "State.h"
#include "Emulator/Emulator.h"
#include "Instructions/Instructions.h"
#include "State_Helpers/State_Helpers.h"

extern State8080 state;

int main(int argc, char *argv[])
{
	// Initialize
	Init_Memory("../../invaders/invaderstest");

	state.b = 0x00;

	state.a = 0x00;
	state.h = 0x21; // hl = 0x2100
	state.l = 0x00;

	uint8_t *hlP = Get_Mem_Byte_P(Get_HL_Address());

	*hlP = 0xaa; // (hl) = 0xaa

	ADD(REG_M);

	printf("a (should have 0xaa): 0x%02x\n", state.a);

	SUB(REG_M);

	printf("a (should have 0x00): 0x%02x\n", state.a);




	// Fetch/execute instructions
	/*
	Execute_Instruction(Fetch_Next_Instruction());
	printf("%s\n", Fetch_Next_Instruction()->mnemonic);
	printf("a: 0x%02x\n", state.a);

	printf("0x%2x\n", *Get_Mem_Byte_P(0x1fff));
	printf("0x%2x\n", *Get_Mem_Byte_P(0x1ffe));

	uint8_t *a = Get_Mem_Byte_P(0x2000);
	*a = 0x20;

	printf("0x%2x\n", *Get_Mem_Byte_P(0x2000));
	printf("0x%2x\n", *Get_Mem_Byte_P(0x4000));
	*/

	getchar();
}