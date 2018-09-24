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

TEST(Logical, RLC)
{
}

TEST(Logical, RRC)
{
}

TEST(Logical, RAL)
{
}

TEST(Logical, RAR)
{
}