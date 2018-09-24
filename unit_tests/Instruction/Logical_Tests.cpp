#include "pch.h"
#include "../unit_tests.h"

TEST(Logical, ANA)
{
	// 0xff & 0x00
	state->a = 0xff;
	state->b = 0x00;

	ANA(REG_B);
	EXPECT_EQ(state->a, 0x00);
	EXPECT_EQ(state->psw.z, 1);
	EXPECT_EQ(state->psw.s, 0);
	EXPECT_EQ(state->psw.p, 1);
}

TEST(Logical, ORA)
{
	// 0x0 | 0xff
	state->a = 0x0;
	state->b = 0xff;
	state->psw.cy = 1;

	ORA(REG_B);
	EXPECT_EQ(state->a, 0xff);
	EXPECT_EQ(state->psw.cy, 0);
	EXPECT_EQ(state->psw.z, 0);
	EXPECT_EQ(state->psw.p, 1);

	// 0x0f | 0xf0
	state->a = 0x0f;
	state->c = 0xf0;

	ORA(REG_C);
	EXPECT_EQ(state->a, 0xff);
	EXPECT_EQ(state->psw.z, 0);
	EXPECT_EQ(state->psw.s, 1);
	EXPECT_EQ(state->psw.p, 1);
}

TEST(Logical, CMP)
{
	// a > b
	state->a = 0x0a;
	state->b = 0x05;

	CMP(REG_B);

	// Carry bit reset - indicating b < a
	EXPECT_EQ(state->psw.cy, 0);

	// Zero bit reset - indicating b != a
	EXPECT_EQ(state->psw.z, 0);

	EXPECT_EQ(state->psw.s, 0);
	EXPECT_EQ(state->psw.p, 1);

	// a == c
	state->a = 0x0;
	state->c = 0x0;

	CMP(REG_C);

	EXPECT_EQ(state->psw.cy, 0);
	EXPECT_EQ(state->psw.z, 1);

	// a < d
	state->a = 0x1;
	state->d = 0x2;

	CMP(REG_D);

	EXPECT_EQ(state->psw.cy, 1);
	EXPECT_EQ(state->psw.z, 0);
}

TEST(Logical, CMA)
{
	state->a = 0x00;

	CMA();
	EXPECT_EQ(state->a, 0xff);

	state->a = 0b01010101;

	CMA();
	EXPECT_EQ(state->a, 0b10101010);
}

// Rotate accumulator left
TEST(Logical, RLC)
{
	state->a = 0b11110010;
	RLC();

	EXPECT_EQ(state->a, 0b11100101);
	EXPECT_EQ(state->psw.cy, 1);
}

// Rotate accumulator right
TEST(Logical, RRC)
{
	state->a = 0b11110010;
	RRC();

	EXPECT_EQ(state->a, 0b01111001);
	EXPECT_EQ(state->psw.cy, 0);
}

// Rotate accumulator left through carry
TEST(Logical, RAL)
{
	state->a = 0b10110101;
	state->psw.cy = 0;
	RAL();

	EXPECT_EQ(state->a, 0b01101010);
	EXPECT_EQ(state->psw.cy, 1);
}

// Rotate accumulator right through carry
TEST(Logical, RAR)
{
	state->a = 0b01101010;
	state->psw.cy = 1;
	RAR();

	EXPECT_EQ(state->a, 0b10110101);
	EXPECT_EQ(state->psw.cy, 0);
}