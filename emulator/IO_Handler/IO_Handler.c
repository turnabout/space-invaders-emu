#include "External_API.h"
#include "IO_Handler.h"

uint8_t Read_Input_Port(uint8_t portN)
{
	switch (portN)
	{
	case 0:
		return Read_Input_Port_0();
	case 1:
		return Read_Input_Port_1();
	case 2:
		return Read_Input_Port_2();
	case 3:
		return Read_Input_Port_3();
	}

	return 0;
}

void Write_Input_Port(uint8_t portN, uint8_t val)
{
	switch (portN)
	{
	case 2:
		Write_Output_Port_2(val);
		break;
	case 3:
		Write_Output_Port_3(val);
		break;
	case 4:
		Write_Output_Port_4(val);
		break;
	case 5:
		Write_Output_Port_5(val);
		break;
	case 6:
		Write_Output_Port_6(val);
		break;
	}
}