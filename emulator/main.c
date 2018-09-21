#include <stdio.h>

#include "State.h"
#include "Instructions/Instructions.h"

int main(int argc, char *argv[])
{
	State8080 *state = Get_State();

	// Test: Check registries
	printf("Should be A (0): %02x\n", *Get_Reg_Address(REG_A));
	printf("Should be A (0): %02x\n", state->a);
	printf("Should be B: %02x\n", *Get_Reg_Address(REG_B));
	printf("Should be C: %02x\n", *Get_Reg_Address(REG_C));
	printf("Should be 77 (L): %02x\n", *Get_Reg_Address(REG_L));

	// Test: Operate instructions & check status afterwards

	ADD(REG_B);
	printf("Accum: %02x\n", state->a); // Should be 0x2b

	ADD(REG_B);
	printf("Accum: %02x\n", state->a); // Should be 0x56

	getchar();
}