#include <stdio.h>

#include "State.h"
#include "Emulator/Emulator.h"
#include "Instructions/Instructions.h"
#include "State_Helpers/State_Helpers.h"

extern State8080 state;

void Interpret_Program_Debug();
void Interpret_Program();

int main(int argc, char *argv[])
{
	Init_Memory("../../invaders/invaders");
	Interpret_Program();

	getchar();
}

// Read through ROM, interpreting instructions
void Interpret_Program()
{
	while (1)
	{
		Execute_Instruction(Fetch_Current_Instruction());
	}
}

// Read through ROM, interpreting instructions
// Print executed instructions as we go along
void Interpret_Program_Debug()
{
	do
	{
		Instruction8080 *inst = Fetch_Current_Instruction();
		Print_Instruction(inst, 0);
		Execute_Instruction(inst);
	} while ((getchar()) != 'q');
}

void Tests()
{
	// SP test
	/*
	// Establish stack
	LXI(SP, 0x24, 0x00);

	// Push BC
	state.b = 0xbb;
	state.c = 0xcc;
	PUSH(REG_B);

	// Pop into DE
	POP(REG_D);

	printf("Should be 0xbbcc: 0x%02x%02x\n", state.d, state.e);
	printf("Should be 0x2400: 0x%02x\n", state.sp);
	*/

	// LDA test
	/*
	uint8_t *src = Get_Mem_Byte_P(0x210a);

	*src = 0xfe;
	LDA(0x21, 0x0a);

	printf("should be 0xfe: 0x%02x\n", state.a);
	*/

	// STA test
	/*
	state.a = 0xda;

	STA(0x20, 0xfe);

	printf("should be 0xda: 0x%02x\n", *Get_Mem_Byte_P(0x20fe));
	*/

	// Call/Return tests
	/*
	state.pc = 0x01;
	CALL(0x04, 0x10);

	printf("PC, should be 0x0410: 0x%04x\n", state.pc);

	RET();
	printf("PC, should be 0x0001: 0x%04x\n", state.pc);
	*/

	// SHLD/LHLD tests
	/*
	uint8_t *p = Get_Mem_Byte_P(0x1020);

	// SHLD
	state.h = 0xee;
	state.l = 0xff;
	SHLD(0x10, 0x20);

	printf("Should be 0xeeff: 0x%02x%02x", *(p + 1), *p);

	*p = 0xbb;
	*(p + 1) = 0xaa;

	// LHLD
	LHLD(0x10, 0x20);

	printf("Should be 0xaabb: 0x%02x%02x", state.h, state.l);
	*/

	// SPHL/XTHL tests
	/*
	state.sp = 0x0100;

	// Load 0x0205 in HL, make SP point there
	LXI(REG_H, 0x02, 0x05);
	SPHL();

	// Load 0xbbcc in BC, push on SP
	LXI(REG_B, 0xbb, 0xcc);
	PUSH(REG_B);

	printf("0x%04x\n", state.sp);

	// Load 0x5577 in HL, swap HL contents for contents SP points at
	LXI(REG_H, 0x55, 0x77);
	XTHL();

	printf("0x%02x%02x (should be 0xbbcc)\n", state.h, state.l);

	printf("0x%02x%02x (should be 0x5577)\n", 
		*Get_Stack_Byte_P(state.sp + 1), 
		*Get_Stack_Byte_P(state.sp)
	);
	*/

	// Stack tests
	/*
	printf("SP: %04x\n", state.sp);

	// Push BC on stack
	state.b = 0xbb;
	state.c = 0xcc;
	PUSH(REG_B);

	// Push DE on stack
	state.d = 0xdd;
	state.e = 0xee;
	PUSH(REG_D);

	// Pop in HL
	POP(REG_H);
	printf("HL (should be 0xddee): 0x%02x%02x\n", state.h, state.l);
	POP(REG_H);
	printf("HL (should be 0xbbcc): 0x%02x%02x\n", state.h, state.l);

	// Push PSW/Accumulator on stack
	state.a = 0xaa;

	state.psw.ac = 1;
	state.psw.cy = 1;
	state.psw.s = 1;
	state.psw.z = 0;
	state.psw.p = 1;

	PUSH(PSW);

	// Reset PSW/Accumulator 
	state.a = 0x00;
	state.psw.ac = 0;
	state.psw.cy = 0;
	state.psw.s = 0;
	state.psw.z = 0;
	state.psw.p = 0;

	printf("Accumulator: 0x%02x\n", state.a);
	printf("ac: %02x\n", state.psw.ac);
	printf("cy: %02x\n", state.psw.cy);
	printf("s: %02x\n", state.psw.s);
	printf("z: %02x\n", state.psw.z);
	printf("p: %02x\n", state.psw.p);

	// Pop back on PSW/Accumulator
	POP(PSW);

	printf("Accumulator: 0x%02x\n", state.a);
	printf("ac: %02x\n", state.psw.ac);
	printf("cy: %02x\n", state.psw.cy);
	printf("s: %02x\n", state.psw.s);
	printf("z: %02x\n", state.psw.z);
	printf("p: %02x\n", state.psw.p);
	*/

	// Fetch/execute instructions test
	/*
	state.a = 0;

	Execute_Instruction(Fetch_Current_Instruction());
	printf("%s\n", Fetch_Current_Instruction()->mnemonic);

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

	// Test LDAX/STAX
	/*
	// BC = 0x2244 (BC) = 0xaaaa
	state.b = 0x22;
	state.c = 0x44;

	uint8_t *adr = Get_Mem_Byte_P(0x2244);
	*adr = 0xaa;

	LDAX(REG_B);

	printf("Should be 0xaa %02x\n", state.a);

	// Store accumulator value into (DE) -> (0x21ef)
	state.a = 0x22;

	state.d = 0x21;
	state.e = 0xef;

	STAX(REG_D);

	printf("Should be 0x22 %02x\n", *Get_Mem_Byte_P(0x21ef));
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

	uint8_t *hlP = Get_Mem_Byte_P(Get_Register_Pair_Pointer(REG_H));

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

}