#include "../Instructions/Instructions.h"

// Memory
// ROM: $0000-$1fff
// RAM: 
//      work RAM:  $2000-23ff
//      video RAM: $23ff-3fff

#define MEM_SIZE   0x8000
#define ROM_SIZE   0x2000
#define STACK_SIZE 0x2000

// Initialize all memory
void Init_Memory(char *romPath);

// Execute a given instruction
Instruction8080 *Fetch_Next_Instruction();
void Execute_Instruction(Instruction8080 *inst);

// Get byte pointer at specified offset in memory
uint8_t *Get_Mem_Byte_P(uint16_t offset);

// Get byte pointer at specified offset in stack memory
uint8_t *Get_Stack_Byte_P(uint16_t offset);

#ifdef _DEBUG
// Print the given instruction - for testing/debugging purposes
void Print_Instruction(Instruction8080 *inst, uint8_t newLine);
#endif