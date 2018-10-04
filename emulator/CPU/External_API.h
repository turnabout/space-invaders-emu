//
// CPU's interface to the outside world
// Used to:
// * Initialize_CPU the CPU's internal API, giving it external functions to access
// * Interpret or fetch the CPU's next instruction
//

#include "typedefs.h"
#include "Instructions/Instructions.h"

// List of bytes corresponding to RST instructions
#define BYTE_RST0 0xc7
#define BYTE_RST1 0xcf
#define BYTE_RST2 0xd7
#define BYTE_RST3 0xdf
#define BYTE_RST4 0xe7
#define BYTE_RST5 0xef
#define BYTE_RST6 0xf7
#define BYTE_RST7 0xff

// Initialize_CPU the CPU's internal API, giving it access to functions for it to
// communicate with the outside world
// getMemBytePFunc: Function used by the CPU to access emulated memory.
// Should return a pointer to the byte at the given offset.
void Initialize_CPU(
	API_Access_Memory getMemBytePFunc,
	API_Read_Input_Port readInputPort,
	API_Write_Input_Port writeInputPort
);

// Interpret the next instruction in line for the CPU
// uint8_t print: Whether to print the interpreted instructions
// uint8_t newLine: Whether to add a newLine after each printed instruction
void Interpret_Next_Instruction(uint8_t print, uint8_t newLine);

// Handle an interrupt. Interpret given data byte as an instruction
// Returns 0 if interrupts were disabled, causing the interrupt to be ignored
int Handle_Interrupt(uint8_t byte);