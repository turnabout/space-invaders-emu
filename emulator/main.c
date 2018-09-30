#include <stdio.h>

#include "CPU/External_API.h"
#include "Memory/External_API.h"
#include "IO_Handler/External_API.h"

#include "Devices/DIP_Switch/DIP_Switch.h"
#include "Devices/Controls/Controls.h"

#include "Frontend/WinAPI.h"

int Loop();

int main(int argc, char *argv[])
{
	Init_Memory("../../invaders/invaders");
	Initialize_CPU(Get_Mem_Byte_P, Read_Input_Port, Write_Input_Port);

	if (!CreateEmulatorWindow(224, 256))
	{
		printf("Error occurred\n");
		return 1;
	}

	return Loop();
}

// Main loop: read through ROM, interpreting instructions
int Loop()
{
	while (1)
	{
		if (!HandleGUI())
		{
			break;
		}

		Interpret_Next_Instruction(1, 1);
	}

	return 0;
}