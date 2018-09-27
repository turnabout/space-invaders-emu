#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "../Instructions/Instructions.h"
#include "../State.h"
#include "Emulator.h"

// Memory allocation containing ROM & RAM
static uint8_t *mem;

// Load ROM into allocated memory
void Load_Rom(char *romPath)
{
	// Attempt getting file to work with
	FILE *f;

	if ((f = fopen(romPath, "rb")) == NULL)
	{
		printf("Error finding file\n\n");
		return;
	}

	// Gather all data into rom buffer
	fread(mem, sizeof(uint8_t), ROM_SIZE, f);
	fclose(f);
}

void Init_Memory(char *romPath)
{
	mem = malloc(MEM_SIZE);

	Load_Rom(romPath);

	// Zero-out RAM (0x2000 - 0x7fff)
	memset(mem + ROM_SIZE, 0, MEM_SIZE - ROM_SIZE);
}

uint8_t *Get_Mem_Byte_P(uint16_t offset)
{
	return mem + offset;
}

uint8_t *Get_Stack_Byte_P(uint16_t offset)
{
	return mem + offset;
}