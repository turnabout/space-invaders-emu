#include <stdio.h>

#include "CPU/External_API.h"
#include "Memory/External_API.h"
#include "IO_Handler/External_API.h"

#include "Devices/DIP_Switch/DIP_Switch.h"
#include "Devices/Controls/Controls.h"
#include "Devices/Sound_Player/Sound_Player.h"

#include "Display/WinAPI.h"

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

		// Handle interrupts coming from display when needed
		if ((interrupt = Check_Display_Interrupt()) != 0)
		{
			Handle_Interrupt(interrupt);
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	Init_Memory("../../invaders/invaders");
	Initialize_CPU(Get_Mem_Byte_P, Read_Input_Port, Write_Input_Port);

	if (!Create_Emulator_Display(2, Get_Mem_Byte_P(VRAM_START)))
	{
		printf("Error occurred creating window\n");
		return 1;
	}

	Init_Sound_Player();

	return Loop();
}