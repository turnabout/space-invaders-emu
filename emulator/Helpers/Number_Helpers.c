#include "Number_Helpers.h"

uint16_t uint8_To_uint16(uint8_t hi, uint8_t lo)
{
	return (uint16_t)(hi << 8) | lo;
}