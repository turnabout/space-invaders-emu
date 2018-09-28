#include <stdint.h>

#include "../Devices/Controls/Controls.h"
#include "../Devices/DIP_Switch/DIP_Switch.h"
#include "../Devices/Shift_Register/Shift_Register.h"

//
// Return data found at specific IO ports
//

// Inputs mapped in hardware - never used by code
uint8_t Read_Input_Port_0();

// Inputs
uint8_t Read_Input_Port_1();

// Inputs
uint8_t Read_Input_Port_2();

// Bit shift register: read
uint8_t Read_Input_Port_3();

//
// Write data to specific IO ports
//

// Bit shift register: set shift amount
void Write_Output_Port_2(uint8_t val);

// Sound bits
void Write_Output_Port_3(uint8_t val);

// Bit shift register: set shift data
void Write_Output_Port_4(uint8_t val);

// Sound bits
void Write_Output_Port_5(uint8_t val);

// Watch-dog
void Write_Output_Port_6(uint8_t val);