#include "Display_Helpers.h"

static unsigned char invertBitsLookup[16] = { 
	0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
	0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf
};

// Reverse bits in a number;
uint8_t Invert_Bits(uint8_t n)
{
   // Invert the top and bottom nibble then swap them
   return (invertBitsLookup[n&0b1111] << 4) | invertBitsLookup[n >> 4];
}
