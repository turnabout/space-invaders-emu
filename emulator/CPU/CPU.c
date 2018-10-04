#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Instructions/Instructions.h"
#include "State.h"
#include "External_API.h"
#include "CPU.h"

extern State8080 state;

// CPU's externally defined functions for accessing memory, io, etc.
API8080 externalFuncs;

// Fetch the instruction currently pointed at by program counter
Instruction8080 *Fetch_Next_Instruction();

// Read and interpret the given instruction
void Interpret_Instruction(Instruction8080 *inst, uint8_t incPc);

#ifdef _DEBUG
void Print_Instruction(Instruction8080 *inst, uint8_t newLine);
#endif

void Initialize_CPU(
	API_Access_Memory getMemBytePFunc,
	API_Read_Input_Port readInputPort,
	API_Write_Input_Port writeInputPort
)
{
	externalFuncs.accessMem = getMemBytePFunc;
	externalFuncs.readInputPort = readInputPort;
	externalFuncs.writeInputPort = writeInputPort;
}

void Interpret_Next_Instruction(uint8_t print, uint8_t newLine)
{
	Instruction8080 *inst = Fetch_Next_Instruction();

	#ifdef _DEBUG
	if (print)
	{
		Print_Instruction(inst, newLine);
	}
	#endif

	Interpret_Instruction(inst, 1);
}

Instruction8080 *Fetch_Next_Instruction()
{
	return Get_Instruction(*externalFuncs.accessMem(state.pc));
}

void Interpret_Instruction(Instruction8080 *inst, uint8_t incPc)
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
		args[argC++] = *externalFuncs.accessMem(state.pc + 1);
	}
	else if (inst->size == 3)
	{
		// Data stored backwards due to little-endian - most significant 
		// byte should be the first argument
		args[argC++] = *externalFuncs.accessMem(state.pc + 2);
		args[argC++] = *externalFuncs.accessMem(state.pc + 1);
	}

	// Increment program counter
	if (incPc)
	{
		state.pc += inst->size;
	}

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

int Handle_Interrupt(uint8_t byte)
{
	if (state.int_enable)
	{
		Interpret_Instruction(Get_Instruction(byte), 0);
		return 1;
	}

	return 0;
}

//
// Debug
//

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
		case REG_M:
			return "M";
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

void Print_Instruction(Instruction8080 *inst, uint8_t newLine)
{
	// Print PC
	printf("%04x:", state.pc);

	// Print instruction
	printf("%-5s", inst->mnemonic);

	// Get first argument(s), if need be
	if (inst->args[0] != -1)
	{
		// RST - only instruction that takes a user-defined uint func arg
		if (strcmp(inst->mnemonic, "RST") == 0)
		{
			printf("%d", inst->args[0]);
		}
		else
		{
			printf("%-3s", Arg_To_Str(inst->args[0]));

			if (inst->args[1] != -1)
			{
				printf("%-3s", Arg_To_Str(inst->args[1]));
			}
		}
	}

	// Get immediate data argument(s), if need be
	if (inst->size == 2)
	{
		printf("0x%02x", *externalFuncs.accessMem(state.pc + 1));
	}
	else if (inst->size == 3)
	{
		printf("0x%02x%02x", *externalFuncs.accessMem(state.pc + 2), *externalFuncs.accessMem(state.pc + 1));
	}
		
	if (newLine == 1)
	{
		printf("\n");
	}
}
#endif