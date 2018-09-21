#include <stdint.h>

void Unimplemented();


// Arithmetic

// ADD: Add register or memory to Accumulator.
// Sets the carry bit if an overflow occurs.
// Resets otherwise.
void ADD(uint8_t reg);

// SUB: Subtract register or memory from accumulator
// Sets the carry bit if NO overflow occurs.
// Resets otherwise.
void SUB(uint8_t reg);