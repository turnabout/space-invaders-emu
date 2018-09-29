// Typedefs used by CPU files
#include <stdint.h>

// Function returning pointer to a byte in emulated memory at the specified 
// offset
typedef uint8_t *(*API_Access_Memory)(uint16_t offset);

// Function for reading from the CPU's input ports, used by the IN instruction
typedef uint8_t(*API_Read_Input_Port)(uint8_t portN);

// Function for writing to the CPU's input ports, used by the OUT instruction
typedef void(*API_Write_Input_Port)(uint8_t portN, uint8_t val);