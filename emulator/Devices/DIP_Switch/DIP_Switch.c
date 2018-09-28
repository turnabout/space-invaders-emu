#include "DIP_Switch.h"

static DIP_Switch dip = {0, 0, 0, 0, 1, 0, 0, 0};

void Set_Switch_Val(uint8_t n, uint8_t val)
{
	*((uint8_t *)&dip + n) = val;
}

uint8_t Get_Switch_Val(uint8_t n)
{
	return *((uint8_t *)&dip + n);
}