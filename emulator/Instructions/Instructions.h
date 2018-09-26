#pragma once

#include <stdint.h>
#include "../Export.h"


//
// Instructions List
//

// Represents a function called by an 8080 Instruction
typedef union {
  void (*No_Args)();
  void (*One_Arg)(uint8_t val);
  void (*Two_Args)(uint8_t val, uint8_t val2);
  void (*Three_Args)(uint8_t val, uint8_t val2, uint8_t val3);
} InstructionFunc8080;

// Represents a 8080 instruction
// Mnemonic is the operation mnemonic only (LXI, MV, RST, etc).
// Size is how many bytes are taken up by the instruction in total.
// Func is the function called by the instruction.
// Args specify one or many optional, first argument(s) used by the called
// function.
// Note: Args[0] MUST be set to -1 if no optional args are included.
//       Args[1] MUST be set to -1 if only the first optional arg is included.
typedef struct Instruction8080 {
	char *mnemonic;
	int size;
	InstructionFunc8080 func;
	int8_t args[2];
} Instruction8080;

Instruction8080 *Get_Instruction(uint8_t instruction);


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


// 
// Data Transfer
//

// MVI: Move immediate data into register/memory
EXPORT void MVI(uint8_t reg, uint8_t data);

// MOV: Move one byte of data from the register specified by the first args, 
// to the register specified by the second args.
EXPORT void MOV(uint8_t regSrc, uint8_t regDst);

// LXI: Load immediate 16-bit value into given register pair
EXPORT void LXI(uint8_t reg, uint8_t hi, uint8_t lo);

// STAX (Store Accumulator): The contents of accumulator are stored in the 
// memory location pointed at by the given register pair
EXPORT void STAX(uint8_t reg);

// LDAX (Load Accumulator): The contents of accumulator are replaced by the 
// the contents at the memory location pointed at by the given register pair
EXPORT void LDAX(uint8_t reg);

// SHLD: Load 16-bit value pointed at by the given 16-bit address into HL
void SHLD(uint8_t hi, uint8_t lo);

// LHLD: Load 16-bit value from HL into the address pointed at by the given 
// 16-bit address
void LHLD(uint8_t hi, uint8_t lo);


// 
// Branch
//

// JMP
// JMP: Jump to given address
EXPORT void JMP(uint8_t hi, uint8_t lo);

// JZ: Jump if Zero = 1
EXPORT void JZ(uint8_t hi, uint8_t lo);

// JNZ: Jump if Zero = 0
EXPORT void JNZ(uint8_t hi, uint8_t lo);

// JC: Jump if Carry = 1
EXPORT void JC(uint8_t hi, uint8_t lo);

// JNC: Jump if Carry = 0
EXPORT void JNC(uint8_t hi, uint8_t lo);

// JPE: Jump if Parity = 1
EXPORT void JPE(uint8_t hi, uint8_t lo);

// JPO: Jump if Parity = 0
EXPORT void JPO(uint8_t hi, uint8_t lo);

// JM: Jump if Sign = 1
EXPORT void JM(uint8_t hi, uint8_t lo);

// JP: Jump if Sign = 0
EXPORT void JP(uint8_t hi, uint8_t lo);

// CALL
// CALL: Push contents of PC onto stack, then jump to given address
EXPORT void CALL(uint8_t hi, uint8_t lo);
EXPORT void CZ(uint8_t hi, uint8_t lo);
EXPORT void CNZ(uint8_t hi, uint8_t lo);
EXPORT void CC(uint8_t hi, uint8_t lo);
EXPORT void CNC(uint8_t hi, uint8_t lo);
EXPORT void CPE(uint8_t hi, uint8_t lo);
EXPORT void CPO(uint8_t hi, uint8_t lo);
EXPORT void CM(uint8_t hi, uint8_t lo);
EXPORT void CP(uint8_t hi, uint8_t lo);

// RET
// RET: Take address on stack & push contents onto PC
EXPORT void RET();
EXPORT void RZ();
EXPORT void RNZ();
EXPORT void RC();
EXPORT void RNC();
EXPORT void RPE();
EXPORT void RPO();
EXPORT void RM();
EXPORT void RP();


// 
// Stack
//

// Helper functions to push value to/pull value from the stack
void Push_Value_On_Stack(uint8_t hi, uint8_t lo);
void Pull_Value_From_Stack(uint8_t *hi, uint8_t *lo);

// PUSH: Push 16-bit data from given register pair (or PSW) onto stack, where
// the stack pointer is currently pointing
void PUSH(uint8_t reg);

// POP: Pop 16-bit data from stack where stack pointer is pointing, and the 
// contents of the given register pair get replaced by it
void POP(uint8_t reg);

// SPHL: Move contents of HL to SP to change its address; SP = HL
void SPHL();

// XTHL: Swap the contents of HL with the 16-bit contents pointed at by SP
// L <-> (SP); H <-> (SP+1)
void XTHL();

// 
// Special
//

// EI: Enable interrupts
void EI();

// DI: Disable interrupts
void DI();

// NOP: No operation. Used to pad timing (takes 4 CPU cycles to execute)
void NOP();

// HLT: Program counter gets incremented like usual, then the CPU enters the
// STOPPED state and no further activity takes place until an interrupt occurs
void HLT();

// IN: Immediate data byte is read from the given input device number and 
// replaces the contents of the accumulator.
void IN(uint8_t deviceN);

// IN: Contents of the accumulator are sent to the given output device number.
void OUT(uint8_t deviceN);

// RST: Restart instruction; special purpose subroutine jump.
// "pos" is the 8-byte subroutine's number (0-7)
void RST(uint8_t pos);

// Used by instructions whose function is unimplemented.
// Certain functions unused by space invaders remain unimplemented.
void NOT_IMPLEMENTED();