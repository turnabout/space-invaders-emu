#include <stdint.h>

#define RAM_START  0x2000
#define VRAM_START 0x2400

// Initialize memory.
// Takes in path used to load ROM into emulated memory
void Init_Memory(char *romPath);

// Get byte pointer at specified offset in memory
uint8_t *Get_Mem_Byte_P(uint16_t offset);