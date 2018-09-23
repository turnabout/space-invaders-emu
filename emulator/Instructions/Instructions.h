#pragma once

#include <stdint.h>
#include "../Export.h"

void Unimplemented();


// Arithmetic

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