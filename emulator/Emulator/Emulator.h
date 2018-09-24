#include "../Instructions/Instructions.h"

// Initialize all memory
void Init_Memory(char *romPath);

// Execute a given instruction
void ExecuteInstruction(Instruction8080 *inst);

// Get byte at specified offset in ROM
uint8_t Get_Rom_Byte(uint16_t offset);