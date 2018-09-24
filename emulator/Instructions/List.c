#include "Instructions.h"
#include "../State.h"

/* 
 * List of all Intel 8080 instructions, in order, with indexes matching opcodes 
 * (0x00 to 0xff).
 */
static struct Instruction8080 list[0xff + 1] = {
	{"NOP", 1, NOP, -1},
	{"ADD", 1, ADD, REG_B},
	{"ADI", 2, ADI, -1},
};

// Get instruction with matching opcode (0x00 through 0xff)
Instruction8080 *Get_Instruction(uint8_t instruction)
{
	return &list[instruction];
}