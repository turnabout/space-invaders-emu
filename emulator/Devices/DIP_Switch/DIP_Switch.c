#include "DIP_Switch.h"

static DIP_Switch dip = {0, 0, 0, 0, 1, 0, 0, 0};

void Set_Switch_Val(uint8_t n, uint8_t val)
{
	uint8_t *nP = ((uint8_t *)&dip);

	*nP ^= ((~val + 1) ^ *nP) & (1 << n);
}

uint8_t Get_Switch_Val(uint8_t n)
{
	return ((1 << n) & *((uint8_t *)&dip)) >> n;
}