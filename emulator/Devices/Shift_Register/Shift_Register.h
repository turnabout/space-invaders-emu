// 
// Dedicated shift hardware
// Since the 8080 instructions don't include one for shifting, an external
// hardware shift register is used.
// 

#include <stdint.h>
#include "../../Export.h"

// Read data from the shift register.
// Returns the most-significant byte shifted to the left by (set offset amount).
EXPORT uint8_t Read_Data();

// Shift the 16-bit value in the register 1 byte to the right, then write the
// given number to the most significant byte.
EXPORT void Write_Data(uint8_t newData);

// Set the register's offset amount. 
// 0 makes Read_Data return the most significant byte.
// 3 would make Read_Data return the MSB shifted to the left by n amount.
EXPORT void Set_Offset(uint8_t newOffset);

#ifdef _DEBUG
EXPORT void Reset_Shift_Register();
#endif