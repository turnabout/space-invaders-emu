#include "Number_Helpers.h"

uint16_t Bytes_To_Short(uint8_t hi, uint8_t lo)
{
	return (uint16_t)(hi << 8) | lo;
}