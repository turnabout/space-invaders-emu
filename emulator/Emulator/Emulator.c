#include "../Instructions/Instructions.h"
#include "../State.h"
#include "Emulator.h"

extern struct State8080 state;

// Read and execute the given instruction
void ExecuteInstruction(Instruction8080 *inst)
{
	// Given args will always be unsigned 8-bit integers
	uint8_t args[3];
	uint8_t argC = 0;

	// Get instruction's argument, if need be
	if (inst->arg != -1)
	{
		args[argC++] = inst->arg;
	}

	// Get immediate data argument(s), if need be
	if (inst->size == 2)
	{
		args[argC++] = Get_Rom_Byte(state.pc + 1);
	}
	else if (inst->size == 3)
	{
		args[argC++] = Get_Rom_Byte(state.pc + 1);
		args[argC++] = Get_Rom_Byte(state.pc + 2);
	}

	// Increment program counter
	state.pc += inst->size;

	// Execute correct instruction function with collected arguments
	switch (argC)
	{
	case 0:
		inst->func.No_Args();
		break;
	case 1:
		inst->func.One_Arg(args[0]);
		break;
	case 2:
		inst->func.Two_Args(args[0], args[1]);
		break;
	case 3:
		inst->func.Three_Args(args[0], args[1], args[2]);
		break;
	}
}