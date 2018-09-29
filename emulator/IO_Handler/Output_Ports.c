#include "IO_Handler.h"

void Write_Output_Port_2(uint8_t val)
{
	// Port 2 only writes bits 0, 1, 2 to shift register offset
	Set_Shift_Register_Offset(val & 0b111);
}

void Write_Output_Port_3(uint8_t val)
{
	// Sound related
}

void Write_Output_Port_4(uint8_t val)
{
	Write_Shift_Register_Data(val);
}

void Write_Output_Port_5(uint8_t val)
{
	// Sound related
}

void Write_Output_Port_6(uint8_t val)
{
}