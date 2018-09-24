#include <stdio.h>

#include "State.h"
#include "Emulator/Emulator.h"
#include "Instructions/Instructions.h"

extern struct State8080 state;

int main(int argc, char *argv[])
{
	// Initialize
	Init_Memory("../../invaders/invaderstest");

	state.b = 0x00;

	// Fetch/execute instructions
	// Execute_Instruction(Fetch_Next_Instruction());
	// printf("%s\n", Fetch_Next_Instruction()->mnemonic);
	// printf("a: 0x%02x\n", state.a);

	getchar();
}