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
	*Get_Register(fixture.reg) = fixture.regVal;
}

TEST(Arithmetic, ADD)
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

TEST(Arithmetic, SUB)
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

TEST(Arithmetic, ADC)
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

TEST(Arithmetic, SBB)
{
	AddSubFixture fixture;

	// 10 - 10 - 1 = 255
	fixture = { REG_A, 10, 10, 255 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	SBB(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);

	// 4 - 3 - 1 = 0
	fixture = { REG_B, 4, 3, 0 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	SBB(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 0);

	// 255 - 255 - 1 = 255
	fixture = { REG_B, 255, 255, 255 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 1;

	SBB(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 1);

	// 10 - 5 = 5
	fixture = { REG_B, 10, 5, 5 };
	Prep_Arithmetic_Test(fixture);
	state->psw.cy = 0;

	SBB(fixture.reg);
	EXPECT_EQ(state->a, fixture.expected);
	EXPECT_EQ(state->psw.cy, 0);
}

TEST(Arithmetic, INR)
{
	*Get_Register(REG_B) = 255;
	INR(REG_B);
	EXPECT_EQ(state->b, 0);

	*Get_Register(REG_L) = 5;
	INR(REG_L);
	EXPECT_EQ(state->l, 6);
}

TEST(Arithmetic, DCR)
{
	*Get_Register(REG_B) = 0;
	DCR(REG_B);
	EXPECT_EQ(state->b, 255);

	*Get_Register(REG_L) = 5;
	DCR(REG_L);
	EXPECT_EQ(state->l, 4);
}

TEST(Arithmetic, ADI)
{
	// 10 + 10 = 20
	state->a = 10;
	ADI(10);

	EXPECT_EQ(state->a, 20);

	// 255 + 10 = 9
	state->a = 255;
	ADI(10);

	EXPECT_EQ(state->a, 9);
	EXPECT_EQ(state->psw.cy, 1);
}

TEST(Arithmetic, SUI)
{
	// 255 - 255 = 0
	state->a = 255;
	SUI(255);

	EXPECT_EQ(state->a, 0);
	EXPECT_EQ(state->psw.cy, 0);

	// 10 - 200 = 66
	state->a = 10;
	SUI(200);

	EXPECT_EQ(state->a, 66);
	EXPECT_EQ(state->psw.cy, 1);
}

// Add immediate w/ carry
TEST(Arithmetic, ACI)
{
	// 10 + 10 + 1 = 21
	state->a = 10;
	state->psw.cy = 1;
	ACI(10);

	EXPECT_EQ(state->a, 21);
	EXPECT_EQ(state->psw.cy, 0);

	// 0 + 255 + 1 = 0
	state->a = 0;
	state->psw.cy = 1;
	ACI(255);

	EXPECT_EQ(state->a, 0);
	EXPECT_EQ(state->psw.cy, 1);
}

// Sub immediate w/ borrow
TEST(Arithmetic, SBI)
{
	// 4 - 3 - 1 = 0
	state->a = 4;
	state->psw.cy = 1;
	SBI(3);

	EXPECT_EQ(state->a, 0);
	EXPECT_EQ(state->psw.cy, 0);

	// 255 - 255 - 1 = 255
	state->a = 255;
	state->psw.cy = 1;
	SBI(255);

	EXPECT_EQ(state->a, 255);
	EXPECT_EQ(state->psw.cy, 1);
}

TEST(Arithmetic, INX)
{
	// bc = 0xaaaa + 1 = 0xaaab
	state->b = 0xaa;
	state->c = 0xaa;

	INX(REG_B);

	EXPECT_EQ(state->b, 0xaa);
	EXPECT_EQ(state->c, 0xab);

	// sp = 0xabcd + 1 = 0xabce
	state->sp = 0xabcd;

	INX(SP);

	EXPECT_EQ(state->sp, 0xabce);

	// de = 0xffff + 1 = 0x0000
	state->d = 0xff;
	state->e = 0xff;

	INX(REG_D);

	EXPECT_EQ(state->d, 0x00);
	EXPECT_EQ(state->e, 0x00);
}

TEST(Arithmetic, DCX)
{
	// bc = 0xaaaa - 1 = 0xaaa9
	state->b = 0xaa;
	state->c = 0xaa;

	DCX(REG_B);

	EXPECT_EQ(state->b, 0xaa);
	EXPECT_EQ(state->c, 0xa9);

	// sp = 0x0000 - 1 = 0xffff
	state->sp = 0x0000;

	DCX(SP);

	EXPECT_EQ(state->sp, 0xffff);
}