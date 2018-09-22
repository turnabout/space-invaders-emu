#pragma once

#include <stdint.h>
#include "Export.h"

// PSW (Program Status Word) condition bits
typedef struct ConditionBits {
	uint8_t z   : 1; // Zero bit
	uint8_t s   : 1; // Sign bit
	uint8_t p   : 1; // Parity bit
	uint8_t cy  : 1; // Carry bit
	uint8_t ac  : 1; // Auxiliary Carry bit
	uint8_t pad : 3; // Padding
} ConditionBits;

// Current 8080 State
typedef struct State8080 {
	uint8_t  a; // Accumulator
	uint8_t  b; // b-c-d-e-h-l Registers
	uint8_t  c;
	uint8_t  d;
	uint8_t  e;
	uint8_t  h;
	uint8_t  l;
	ConditionBits psw;  // Program Status Word
	uint8_t int_enable; // Interrupt
	uint16_t sp;        // Stack pointer
	uint16_t pc;        // Program counter
	uint8_t *memory;    // Address pointed at by registers h/l
} State8080;

// Offset in memory bytes for each of the State8080 struct members
#define REG_A      0
#define REG_B      1
#define REG_C      2
#define REG_D      3
#define REG_E      4
#define REG_H      5
#define REG_L      6
#define PSW        7
#define INT_ENABLE 8
#define SP         9
#define PC         11
#define REG_MEMORY 13

// API

// Get a register's address (in our emulator memory-space)
// Memory (M) - returns address HL is pointing to
EXPORT uint8_t *Get_Reg_Address(uint8_t offset);

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

// Get current global 8080 state
EXPORT State8080 *Get_State();

// Debug only
#ifdef _DEBUG
// Reset the current State8080.
EXPORT void Reset_State();
#endif