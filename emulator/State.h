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
} State8080;

// Values representing each member of the State8080 struct, with the exception
// of REG_M, which represents the address pointed by HL
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
#define REG_M      12 // Address pointed by HL


//
// Debug only
//

#ifdef _DEBUG
// Get current global 8080 state
EXPORT State8080 *Get_State();

// Reset the current State8080.
EXPORT void Reset_State();
#endif