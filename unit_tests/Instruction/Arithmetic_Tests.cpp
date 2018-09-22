#include "pch.h"
#include "../unit_tests.h"

typedef struct AddSubFixture {
	uint8_t reg;
	uint8_t accumVal;
	uint8_t regVal;
	uint8_t expected;
} AddSubFixture;

// Test an ADD or SUB
void Test_Add_Sub(AddSubFixture fixture, ConditionBits expectedPsw, uint8_t isAdd)
{
	uint8_t *reg = Get_Reg_Address(fixture.reg);

	state->a = fixture.accumVal;
	*reg = fixture.regVal;

	if (isAdd)
	{
		ADD(fixture.reg);
	}
	else
	{
		SUB(fixture.reg);
	}

	// Expected value
	EXPECT_EQ(state->a, fixture.expected);

	// Expected PSW
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);
}

TEST(Instructions_Arithmetic, ADD)
{
	Test_Add_Sub({ // 0x0 + 0xa = 0xa
			REG_B, // Which register
			0x0,   // Accumulator value
			0xa,   // Register value
			0xa    // Expected value
		}, {
			0, // Zero
			0, // Sign
			1, // Parity
			0  // Carry
		},
		1
	);

	// C: 10 + 100 = 110
	Test_Add_Sub(
		{REG_C, 10, 100, 110}, 
		{0, 0, 0, 0}, 1
	);

	// D: 240 + 15 = 255
	Test_Add_Sub(
		{REG_D, 0b11110000, 0b00001111, 0b11111111}, 
		{0, 1, 1, 0}, 1
	);

	// A: 0 + 0 = 0
	Test_Add_Sub(
		{REG_A, 0, 0, 0}, 
		{1, 0, 1, 0}, 1
	);

	// E: 250 + 50 = (truncated) 44
	Test_Add_Sub(
		{REG_E, 250, 50, 44}, 
		{0, 0, 1, 1}, 1
	);

	// Memory: 10 + 10 = 20
	Test_Add_Sub(
		{REG_MEMORY, 10, 10, 10}, 
		{0, 0, 1, 1}, 1
	);
}