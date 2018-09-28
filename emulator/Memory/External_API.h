#include <stdint.h>

// Initialize memory.
// Takes in path used to load ROM into emulated memory
void Init_Memory(char *romPath);

// Get byte pointer at specified offset in memory
uint8_t *Get_Mem_Byte_P(uint16_t offset);