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

	// Fetch/execute instructions test
	/*
	state.a = 0;

	Execute_Instruction(Fetch_Next_Instruction());
	printf("%s\n", Fetch_Next_Instruction()->mnemonic);

	printf("a: 0x%02x\n", state.a);
	*/

	// Get_Mem_Byte_P test
	/*
	printf("0x%2x\n", *Get_Mem_Byte_P(0x1fff));
	printf("0x%2x\n", *Get_Mem_Byte_P(0x1ffe));

	uint8_t *a = Get_Mem_Byte_P(0x2000);
	*a = 0x20;

	printf("0x%2x\n", *Get_Mem_Byte_P(0x2000));
	printf("0x%2x\n", *Get_Mem_Byte_P(0x4000));
	*/

	// MOV/MVI test
	/*
	// HL points to 0x2100
	state.h = 0x21;
	state.l = 0x00;
	MVI(REG_M, 0x8a); // move 0x8a to (hl)
	printf("Should 8a %02x\n", *Get_HL_Pointer());

	MOV(REG_A, REG_M);
	printf("Should 8a %02x\n", state.a);

	state.b = 0x49;
	MOV(REG_M, REG_B); // move REG_B(0x49) to (hl)
	printf("Should 49 %02x\n", *Get_HL_Pointer());
	*/

	// REG_M tests
	/*
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


	INR(REG_M);
	printf("(hl) (should have 0xab): 0x%02x\n", *hlP);
	DCR(REG_M);
	printf("(hl) (should have 0xaa): 0x%02x\n", *hlP);

	*hlP = 0x01;
	state.a = 0x00;

	CMP(REG_M);

	printf("Should be 0: %d\n", state.psw.z);
	printf("Should be 1: %d\n", state.psw.cy);
	*/

	getchar();
}