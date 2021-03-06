#pragma once

#include "../../Export.h"
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

// Get actual pointer in emulated memory, pointed at by (register pair)
EXPORT uint8_t *Get_Register_Pair_Pointer(uint8_t reg);

// Get a given register's value for instructions.
// Takes in a register (REG_B, REG_C, etc) and returns the value held by it.
// If the given register is REG_M, returns (HL)
uint8_t Get_Instruction_Reg_Val(uint8_t reg);


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
// isAddition: Whether the operation that produced the opRes is an addition
EXPORT void PSW_Update_Carry_Bit(uint8_t opRes, uint8_t operand, uint8_t isAddition);

// Update Carry Bit 16: same as PSW_Update_Carry_Bit, but checks the result
// of a 16-bit operation.
EXPORT void PSW_Update_Carry_Bit_16(uint16_t opRes, uint16_t operand, uint8_t isAddition);

// Update all PSW bits
EXPORT void PSW_Update_All(uint8_t opRes, uint8_t operand, uint8_t isAddition);

// Update the Auxiliary Carry Bit, which is set if there was a carry out of bit 3
EXPORT void PSW_Update_Auxiliary_Carry_Bit(uint8_t opRes, uint8_t operand1);