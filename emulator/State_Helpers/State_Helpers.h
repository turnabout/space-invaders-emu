#pragma once

#include "../Export.h"
#include "../State.h"


//
// Register
//

// Get pointer to a register (in our emulator memory-space)
// Memory (M) - returns address HL is pointing to
EXPORT uint8_t *Get_Register(uint8_t offset);

// Get specified register pair (PSW[+A], REG_B[+C], REG_D[+E], REG_H[+L])
// Sets into given uint8_t pointer
// When SP, only one 16-bit pointer is set into regPair
EXPORT void Get_Register_Pair(uint8_t regPair, uint8_t **regs);

// Get 16-bit value stored in register pair
EXPORT uint16_t Get_Register_Pair_Val(uint8_t regPair);

// Store a 16-bit value in a register pair
EXPORT void Store_Register_Pair_Val(uint8_t reg, uint16_t val);

// Get the address pointed at by HL
EXPORT uint16_t Get_HL_Address();

// Get actual pointer in emulated memory, pointed at by (HL)
EXPORT uint8_t *Get_HL_Pointer();

// Get actual pointer in emulated memory, pointed at by (register pair)
EXPORT uint8_t *Get_Register_Pair_Pointer(uint8_t reg);


//
// PSW
//

// Update Sign Bit: sets if instruction result most significant bit is 1
EXPORT void PSW_Update_Sign_Bit(uint8_t opRes);

// Update Zero Bit: sets if instruction result is = zero.
EXPORT void PSW_Update_Zero_Bit(uint8_t opRes);

// Update Parity Bit: sets if instruction result has even set bits
EXPORT void PSW_Update_Parity_Bit(uint8_t opRes);

// Update Carry Bit: sets if instruction result has resulted in a carry out or 
// borrow into the most significant bit.
// operand: The first operand of the additon/subtraction that led to the opRes.
// valIfOverflow: The value to update the carry bit with if there was an 
// overflow. Additions use 1, subtractions use 0.
EXPORT void PSW_Update_Carry_Bit(uint8_t opRes, uint8_t operand, uint8_t valIfOverflow);

// Update Carry Bit 16: same as PSW_Update_Carry_Bit, but checks the result
// of a 16-bit operation.
EXPORT void PSW_Update_Carry_Bit_16(uint16_t opRes, uint16_t operand, uint8_t valIfOverflow);

// Update all PSW bits
EXPORT void PSW_Update_All(uint8_t opRes, uint8_t operand, uint8_t valIfOverflow);