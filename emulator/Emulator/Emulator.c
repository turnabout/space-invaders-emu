#include <stdio.h>

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

	// Get first argument(s), if need be
	if (inst->args[0] != -1)
	{
		args[argC++] = inst->args[0];

		if (inst->args[1] != -1)
		{
			args[argC++] = inst->args[1];
		}
	}

	// Get immediate data argument(s), if need be
	if (inst->size == 2)
	{
		args[argC++] = *Get_Mem_Byte_P(state.pc + 1);
	}
	else if (inst->size == 3)
	{
		// Data stored backwards due to little-endian - most significant 
		// byte should be the first argument
		args[argC++] = *Get_Mem_Byte_P(state.pc + 2);
		args[argC++] = *Get_Mem_Byte_P(state.pc + 1);
	}

	// Increment program counter
	state.pc += inst->size;

	// Execute correct instruction function with collected arguments
	// Note: Not a single instruction function uses 4 arguments
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

#ifdef _DEBUG
char *Arg_To_Str(uint8_t val)
{
	switch (val)
	{
		case REG_A:
			return "A";
			break;
		case REG_B:
			return "B";
			break;
		case REG_C:
			return "C";
			break;
		case REG_D:
			return "D";
			break;
		case REG_E:
			return "E";
			break;
		case REG_H:
			return "H";
			break;
		case REG_L:
			return "L";
			break;
		case PSW:
			return "PSW";
			break;
		case SP:
			return "SP";
			break;
	}
	return "UNK";
}

void Print_Instruction(Instruction8080 *inst)
{
	// Print PC
	printf("0x%04x: ", state.pc);

	// Print instruction
	printf("%5s", inst->mnemonic);

	// Get first argument(s), if need be
	if (inst->args[0] != -1)
	{
		// RST - only instruction that takes a user-defined uint func arg
		if (inst->mnemonic[0] == 'R' &&
			inst->mnemonic[1] == 'S' &&
			inst->mnemonic[2] == 'T')
		{
			printf("%d", inst->args[0]);
		}
		else
		{
			printf("%3s", Arg_To_Str(inst->args[0]));

			if (inst->args[1] != -1)
			{
				printf("%3s", Arg_To_Str(inst->args[1]));
			}
		}
	}

	// Get immediate data argument(s), if need be
	if (inst->size == 2)
	{
		printf("0x%02x", *Get_Mem_Byte_P(state.pc + 1));
	}
	else if (inst->size == 3)
	{
		printf("0x%02x%02x", *Get_Mem_Byte_P(state.pc + 2), *Get_Mem_Byte_P(state.pc + 1));
	}

	printf("\n");
}
#endif