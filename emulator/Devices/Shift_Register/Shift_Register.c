#include "Shift_Register.h"

// Current data in the register
static uint16_t registerData = 0x0000;

// The returned 8-bit result offset
static uint8_t resultOffset = 0;

uint8_t Read_Shift_Register_Data()
{
	return registerData >> (8 - resultOffset);
}

void Write_Shift_Register_Data(uint8_t newData)
{
	registerData >>= 8;
	registerData = (uint16_t)(newData << 8) | registerData;
}

void Set_Shift_Register_Offset(uint8_t newOffset)
{
	resultOffset = newOffset;
}

#ifdef _DEBUG
void Reset_Shift_Register()
{
	registerData = 0x0000;
	resultOffset = 0;
}
#endif