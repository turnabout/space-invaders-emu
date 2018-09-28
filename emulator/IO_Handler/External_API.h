// 
// IO Handler
// Links CPU's IN/OUT instructions with the appropriate data, connecting to 
// 'device' modules.
// 

#include <stdint.h>

// Return value found at the given port number.
uint8_t Read_Input_Port(uint8_t portN);

// Set given value at the given port number.
void Write_Input_Port(uint8_t portN, uint8_t val);