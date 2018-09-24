#include <stdio.h> 
#include <stdlib.h>

#include "../Instructions/Instructions.h"
#include "../State.h"
#include "Emulator.h"

// Memory allocation containing our ROM
static uint8_t *rom;

// Load ROM into memory
void Load_Rom(char *romPath)
{
	// Allocate memory
	rom = malloc((sizeof(uint8_t)) * ROM_SIZE);

	// Attempt getting file to work with
	FILE *f;

	if ((f = fopen(romPath, "rb")) == NULL)
	{
		printf("Error finding file\n\n");
		return;
	}

	// Gather all data into rom buffer
	fread(rom, sizeof(uint8_t), ROM_SIZE, f);
	fclose(f);
}

void Init_Memory(char *romPath)
{
	Load_Rom(romPath);
}

uint8_t Get_Rom_Byte(uint16_t offset)
{
	return *(rom + offset);
}