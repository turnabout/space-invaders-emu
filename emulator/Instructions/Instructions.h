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