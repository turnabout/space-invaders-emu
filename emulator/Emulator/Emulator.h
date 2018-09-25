#include "../Export.h"
#include "../Instructions/Instructions.h"

// Memory
// ROM: $0000-$1fff
// RAM: 
//      work RAM:  $2000-23ff
//      video RAM: $23ff-3fff

#define MEM_SIZE 0x8000
#define ROM_SIZE 0x2000

// Initialize all memory
EXPORT void Init_Memory(char *romPath);

// Execute a given instruction
Instruction8080 *Fetch_Next_Instruction();
void Execute_Instruction(Instruction8080 *inst);

// Get byte pointer at specified offset in memory
EXPORT uint8_t *Get_Mem_Byte_P(uint16_t offset);