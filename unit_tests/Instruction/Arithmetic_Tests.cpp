#include "pch.h"
#include "../unit_tests.h"

typedef struct AddSubFixture {
	uint8_t reg;
	uint8_t accumVal;
	uint8_t regVal;
	uint8_t expected;
} AddSubFixture;

// Test an ADD or SUB
void Prep_Arithmetic_Test(AddSubFixture fixture, ConditionBits expectedPsw, uint8_t isAdd)
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
}

TEST(Instructions_Arithmetic, ADD)
{

	AddSubFixture fixture;
	ConditionBits expectedPsw;

	fixture = { // 0x0 + 0xa = 0xa
		REG_B, // Which register
		0x0,   // Accumulator value
		0xa,   // Register value
		0xa    // Expected value
	};

	expectedPsw = {
		0, // Zero
		0, // Sign
		1, // Parity
		0  // Carry
	};
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// C: 10 + 100 = 110
	fixture = {REG_C, 10, 100, 110};
	expectedPsw = { 0, 0, 0, 0 };
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// D: 240 + 15 = 255
	fixture = {REG_D, 0b11110000, 0b00001111, 0b11111111};
	expectedPsw = { 0, 1, 1, 0 };
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// A: 0 + 0 = 0
	fixture = { REG_A, 0, 0, 0 };
	expectedPsw = { 1, 0, 1, 0 };
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// E: 250 + 50 = (truncated) 44
	fixture = { REG_E, 250, 50, 44 };
	expectedPsw = { 0, 0, 0, 1 };
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// Memory: 10 + 10 = 20
	fixture = { REG_MEMORY, 10, 10, 20 };
	expectedPsw = { 0, 0, 1, 0 };
	Prep_Arithmetic_Test(fixture, expectedPsw, 1);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);
}