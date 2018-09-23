#include <stdio.h>

#include "State.h"
#include "Instructions/Instructions.h"

int main(int argc, char *argv[])
{
	State8080 *state = Get_State();

	// Test: Check registries
	printf("Should be A (0): %02x\n", *Get_Register(REG_A));
	printf("Should be A (0): %02x\n", state->a);
	printf("Should be B: %02x\n", *Get_Register(REG_B));
	printf("Should be C: %02x\n", *Get_Register(REG_C));
	printf("Should be 77 (L): %02x\n", *Get_Register(REG_L));

	// Test: Operate instructions & check status afterwards

	ADD(REG_B);
	printf("Accum: %02x\n", state->a); // Should be 0x2b

	ADD(REG_B);
	printf("Accum: %02x\n", state->a); // Should be 0x56



	uint8_t a, b, c;
	uint16_t full;

	a = 0b00000100;
	b = 0b00000011;

	// c = a - b;
	// c = a + (~b + 1);
	c = a + (~b + 1);
	full = (uint16_t)a + (uint16_t)(~b + 1);

	printf("%d\n", c);
	printf("%04x\n", c);

	printf("full: %d\n", full);
	printf("full: %04x\n", full);

	getchar();
}