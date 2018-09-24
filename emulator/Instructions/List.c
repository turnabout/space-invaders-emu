#include "Instructions.h"
#include "../State.h"

/* 
 * List of all Intel 8080 instructions, in order, with indexes matching opcodes 
 * (0x00 to 0xff).
 */
static struct Instruction8080 list[0xff + 1] = {
	{"NOP", 1, NOP, -1},
	{"ADD", 1, ADD, REG_B},
};

// Get instruction with matching opcode (0x00 through 0xff)
struct Instruction8080 *GetInstruction(int instruction)
{
	return &list[instruction];
}