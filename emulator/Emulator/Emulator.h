#include "../Instructions/Instructions.h"

#define ROM_SIZE 0x2000

// Initialize all memory
void Init_Memory(char *romPath);

// Execute a given instruction
Instruction8080 *Fetch_Next_Instruction();
void Execute_Instruction(Instruction8080 *inst);

// Get byte at specified offset in ROM
uint8_t Get_Rom_Byte(uint16_t offset);