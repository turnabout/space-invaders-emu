#include "IO_Handler.h"
#include "../Devices/Sound_Player/Sound_Player.h"

// Write data to an audio output (ports 3/5).
// prevVal:  The value that was previously passed to this output port.
//           Should be defined as a static variable within the port's function.
// newVal:   The value newly passed to this output port
// firstSfx: The number of the first SFX handled by this port.
//           Port 3 should use SFX_UFO (0).
//           Port 5 should use SFX_Fleet_Movement_1 (4).
// Return:   The value to update the port's prevVal with.
uint8_t Write_Audio_Output(uint8_t prevVal, uint8_t newVal, uint8_t offset);

void Write_Output_Port_2(uint8_t val)
{
	// Port 2 only writes bits 0, 1, 2 to shift register offset
	Set_Shift_Register_Offset(val & 0b111);
}

void Write_Output_Port_3(uint8_t val)
{
	static uint8_t prevVal;
	prevVal = Write_Audio_Output(prevVal, val, SFX_UFO);
}

void Write_Output_Port_4(uint8_t val)
{
	Write_Shift_Register_Data(val);
}

void Write_Output_Port_5(uint8_t val)
{
	static uint8_t prevVal;
	prevVal = Write_Audio_Output(prevVal, val, SFX_Fleet_Movement_1);
}

void Write_Output_Port_6(uint8_t val)
{
}

uint8_t Write_Audio_Output(uint8_t prevVal, uint8_t newVal, uint8_t offset)
{
	// Ignore if completely unchanged
	if (newVal == prevVal)
	{
		return prevVal;
	}

	// See which value(s) were toggled & handle
	for (int i = 0; i < 4; i++)
	{
		uint8_t newBit;

		// Different value detected at bit i
		if ((newBit = ((newVal >> i) & 1)) != ((prevVal >> i) & 1))
		{
			if (newBit) // Bit toggled on
			{
				Play_Sound(i + offset);
			}
			else // Bit toggled off
			{
				Stop_Sound(i + offset);
			}
		}
	}

	// Set prevVal to new val
	return newVal;
}