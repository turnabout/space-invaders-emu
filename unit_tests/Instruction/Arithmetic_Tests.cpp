#include "pch.h"
#include "../unit_tests.h"

typedef struct AddSubFixture {
	uint8_t reg;
	uint8_t accumVal;
	uint8_t regVal;
	uint8_t expected;
} AddSubFixture;

// Test an ADD or SUB
void Prep_Arithmetic_Test(AddSubFixture fixture)
{
	state->a = fixture.accumVal;
	*Get_Reg_Address(fixture.reg) = fixture.regVal;
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
	Prep_Arithmetic_Test(fixture);
	ADD(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// C: 10 + 100 = 110
	fixture = {REG_C, 10, 100, 110};
	expectedPsw = { 0, 0, 0, 0 };
	Prep_Arithmetic_Test(fixture);
	ADD(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// D: 240 + 15 = 255
	fixture = {REG_D, 0b11110000, 0b00001111, 0b11111111};
	expectedPsw = { 0, 1, 1, 0 };
	Prep_Arithmetic_Test(fixture);
	ADD(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// A: 0 + 0 = 0
	fixture = { REG_A, 0, 0, 0 };
	expectedPsw = { 1, 0, 1, 0 };
	Prep_Arithmetic_Test(fixture);
	ADD(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// E: 250 + 50 = (truncated) 44
	fixture = { REG_E, 250, 50, 44 };
	expectedPsw = { 0, 0, 0, 1 };
	Prep_Arithmetic_Test(fixture);
	ADD(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// Memory: 10 + 10 = 20
	fixture = { REG_MEMORY, 10, 10, 20 };
	expectedPsw = { 0, 0, 1, 0 };
	Prep_Arithmetic_Test(fixture);

	// TODO
	/*
	ADD(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);
	*/
}

TEST(Instructions_Arithmetic, SUB)
{
	AddSubFixture fixture;
	ConditionBits expectedPsw;

	// A: 10 - 10 = 0
	fixture = { REG_A, 10, 10, 0 }; // Reg, AccumVal, RegVal, ExpectedVal
	expectedPsw = { 1, 0, 1, 0 }; // Zero, Sign, Parity, Carry
	Prep_Arithmetic_Test(fixture);
	SUB(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// B: 200 - 100 = 100
	fixture = { REG_B, 200, 100, 100 };
	expectedPsw = { 0, 0, 0, 0 };
	Prep_Arithmetic_Test(fixture);
	SUB(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// D: 10 - 5 = 0
	fixture = { REG_D, 10, 5, 5 };
	expectedPsw = { 0, 0, 1, 0 };
	Prep_Arithmetic_Test(fixture);
	SUB(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// C: 10 - 100 = 166
	fixture = { REG_B, 10, 100, 166 };
	expectedPsw = { 0, 1, 1, 1 };
	Prep_Arithmetic_Test(fixture);
	SUB(fixture.reg);

	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);

	// M: 10 - 100 = 166
	fixture = { REG_MEMORY, 10, 100, 166 };
	expectedPsw = { 0, 1, 1, 1 };
	Prep_Arithmetic_Test(fixture);

	// TODO
	/*
	SUB(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.z, expectedPsw.z);
	EXPECT_EQ(state->psw.s, expectedPsw.s);
	EXPECT_EQ(state->psw.p, expectedPsw.p);
	EXPECT_EQ(state->psw.cy, expectedPsw.cy);
	*/
}

TEST(Instructions_Arithmetic, ADC)
{
	AddSubFixture fixture;

	// A: 10 + 10 + 1 = 21
	fixture = { REG_A, 10, 10, 21 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 0);

	// D: 0 + 255 + 1 = 0
	fixture = { REG_D, 0, 255, 0 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);

	// L: 50 + 50 + 0 = 100
	fixture = { REG_L, 50, 50, 100 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 0;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 0);

	// L: 255 + 0 + 1 = 0
	fixture = { REG_L, 255, 0, 0 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);

	// B: 255 + 10 + 0 = 9
	fixture = { REG_B, 255, 10, 9 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 0;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);

	// C: 255 + 255 + 1 = 255
	fixture = { REG_B, 255, 255, 255 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	ADC(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);
}