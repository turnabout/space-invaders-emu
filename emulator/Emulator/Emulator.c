#include "../Instructions/Instructions.h"
#include "../State.h"
#include "Emulator.h"

extern struct State8080 state;

// Fetch the next instruction in ROM pointed at by current program counter
Instruction8080 *Fetch_Next_Instruction()
{
	return Get_Instruction(*Get_Mem_Byte_P(state.pc));
}

// Read and execute the given instruction
void Execute_Instruction(Instruction8080 *inst)
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
		args[argC++] = *Get_Mem_Byte_P(state.pc + 1);
	}
	else if (inst->size == 3)
	{
		args[argC++] = *Get_Mem_Byte_P(state.pc + 1);
		args[argC++] = *Get_Mem_Byte_P(state.pc + 2);
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
		inst->func.One_Arg((uint8_t)args[0]);
		break;
	case 2:
		inst->func.Two_Args((uint8_t)args[0], (uint8_t)args[1]);
		break;
	case 3:
		inst->func.Three_Args((uint8_t)args[0], (uint8_t)args[1], (uint8_t)args[2]);
		break;
	}
}