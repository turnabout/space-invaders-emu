#pragma once

#include <stdint.h>
#include "../Export.h"

void Unimplemented();


//
// Arithmetic
//

// ADD: Add register or memory to Accumulator.
// Sets the carry bit if an overflow occurs.
EXPORT void ADD(uint8_t reg);

// ADC: Add register or memory plus the contents of the carry bit to Accumulator
EXPORT void ADC(uint8_t reg);

// SUB: Subtract register or memory from accumulator
// Sets the carry bit if NO overflow occurs.
EXPORT void SUB(uint8_t reg);

// SBB: Subtract register or memory from accumulator with borrow
EXPORT void SBB(uint8_t reg);

// Increment register or memory. Does not affect carry bit
EXPORT void INR(uint8_t reg);

// Decrement register or memory. Does not affect carry bit
EXPORT void DCR(uint8_t reg);

// Add immediate byte to the Accumulator
EXPORT void ADI(uint8_t val);

// Add immediate byte to the Accumulator with carry
EXPORT void ACI(uint8_t val);

// Subtract immediate byte from the Accumulator
EXPORT void SUI(uint8_t val);

// Subtract immediate byte from the Accumulator with borrow
EXPORT void SBI(uint8_t val);

// INX: Increment 16-bit number held in specified register pair
EXPORT void INX(uint8_t reg);

// DCX: Decrement 16-bit number held in specified register pair
EXPORT void DCX(uint8_t reg);

// DAD: The 16-bit number in the specified register pair is added to the 
// 16-bit number in HL
EXPORT void DAD(uint8_t reg);


//
// Logical
//

// ANA: AND register or memory with accumulator
EXPORT void ANA(uint8_t reg);

// ORA: OR register or memory with accumulator
EXPORT void ORA(uint8_t reg);

// XRA: XOR register or memory with accumulator
EXPORT void XRA(uint8_t reg);

// ANA: AND immediate byte with accumulator
EXPORT void ANI(uint8_t val);

// ORA: OR immediate byte with accumulator
EXPORT void ORI(uint8_t val);

// XRA: XOR immediate byte with accumulator
EXPORT void XRI(uint8_t val);

// CMP: Compare register or memory with accumulator
EXPORT void CMP(uint8_t reg);

// CMA: Complement accumulator (A = ~A)
EXPORT void CMA();

// RLC: Rotate accumulator left
EXPORT void RLC();

// RRC: Rotate accumulator right
EXPORT void RRC();

// RAL: Rotate accumulator left through carry
EXPORT void RAL();

// RAR: Rotate accumulator right through carry
EXPORT void RAR();

// CMC: Complement carry flag (cy = ~cy)
EXPORT void CMC();

// STC: Set carry flag to 1
EXPORT void STC();