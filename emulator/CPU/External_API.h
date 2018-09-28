//
// CPU's interface to the outside world
// Used to:
// * Initialize_CPU the CPU's internal API, giving it external functions to access
// * Interpret or fetch the CPU's next instruction
//

#include "typedefs.h"
#include "Instructions/Instructions.h"

// Initialize_CPU the CPU's internal API, giving it access to functions for it to
// communicate with the outside world
// getMemBytePFunc: Function used by the CPU to access emulated memory.
// Should return a pointer to the byte at the given offset.
void Initialize_CPU(
	API_Access_Memory getMemBytePFunc
);

// Interpret the next instruction in line for the CPU
// uint8_t print: Whether to print the interpreted instructions
// uint8_t newLine: Whether to add a newLine after each printed instruction
void Interpret_Next_Instruction(uint8_t print, uint8_t newLine);