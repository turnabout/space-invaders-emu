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

	if (!CreateEmulatorWindow(300, 300))
	{
		printf("Error occurred creating window\n");
		return 1;
	}

	// Initialize the display, enabling it to draw
	Initialize_Display(Get_Mem_Byte_P(VRAM_START));

	return Loop();
}

// Main loop: read through ROM, interpreting instructions
int Loop()
{
	uint8_t interrupt = 0;

	while (1)
	{
		if (!Handle_GUI())
		{
			break;
		}

		Interpret_Next_Instruction(0, 1);

		if ((interrupt = Check_Display_Interrupt()) != 0)
		{
			Handle_Interrupt(interrupt);
		}
	}

	return 0;
}