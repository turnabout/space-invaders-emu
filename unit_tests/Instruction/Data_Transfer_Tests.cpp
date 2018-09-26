#include "pch.h"
#include "../unit_tests.h"

TEST(Data_Transfer, MVI)
{
	state->a = 0x0;
	MVI(REG_A, 0xab);

	EXPECT_EQ(state->a, 0xab);
}

TEST(Data_Transfer, MOV)
{
	state->a = 0x0;
	state->b = 0x58;
	MOV(REG_A, REG_B);

	EXPECT_EQ(state->a, 0x58);
}

TEST(Data_Transfer, LXI)
{
	uint8_t hi, lo;

	// Load 0x2211 into BC, so
	// B = 0x22 C = 0x11
	hi = 0x22;
	lo = 0x11;
	LXI(REG_B, hi, lo);

	EXPECT_EQ(state->b, hi);
	EXPECT_EQ(state->c, lo);

	// Load 0xbbaa into DE, so
	// D = 0xbb E = 0xaa
	hi = 0xbb;
	lo = 0xaa;
	LXI(REG_D, hi, lo);

	EXPECT_EQ(state->d, hi);
	EXPECT_EQ(state->e, lo);

	// Load 0xe23f into SP
	hi = 0xe2;
	lo = 0x3f;
	LXI(SP, hi, lo);

	EXPECT_EQ(state->sp, 0xe23f);
}

TEST(Data_Transfer, PCHL)
{
	state->h = 0x10;
	state->l = 0x55;

	PCHL();

	EXPECT_EQ(state->pc, 0x1055);
}

TEST(Data_Transfer, XCHG)
{
	state->h = 0x10;
	state->l = 0x55;

	state->d = 0xdd;
	state->e = 0xee;

	XCHG();

	EXPECT_EQ(state->h, 0xdd);
	EXPECT_EQ(state->l, 0xee);
	EXPECT_EQ(state->d, 0x10);
	EXPECT_EQ(state->e, 0x55);
}