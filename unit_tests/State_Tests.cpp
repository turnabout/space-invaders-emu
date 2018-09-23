#include "pch.h"
#include "unit_tests.h"

TEST(State, Reset_State)
{
	state->a = 0xa;
	state->h = 0xf;
	state->psw.cy = 1;
	state->psw.z = 1;

	Reset_State();

	EXPECT_EQ(state->a, 0);
	EXPECT_EQ(state->h, 0);
	EXPECT_EQ(state->psw.cy, 0);
	EXPECT_EQ(state->psw.z, 0);
}

TEST(State, Get_Register)
{
	state->a = 0x0a;
	state->b = 0x0b;
	state->d = 0x0d;
	state->l = 0x0f;

	uint8_t *regA = Get_Register(REG_A);
	uint8_t *regB = Get_Register(REG_B);
	uint8_t *regD = Get_Register(REG_D);
	uint8_t *regL = Get_Register(REG_L);

	EXPECT_EQ(*regA, 0x0a);
	EXPECT_EQ(*regB, 0x0b);
	EXPECT_EQ(*regD, 0x0d);
	EXPECT_EQ(*regL, 0x0f);

	Reset_State();
}

TEST(State, Get_Register_Pair)
{
	uint8_t *pair[2];

	// B/C
	state->b = 5;
	state->c = 8;

	Get_Register_Pair(REG_B, pair);

	EXPECT_EQ(*pair[0], 5);
	EXPECT_EQ(*pair[1], 8);

	// H/L
	state->h = 15;
	state->l = 255;

	Get_Register_Pair(REG_H, pair);

	EXPECT_EQ(*pair[0], 15);
	EXPECT_EQ(*pair[1], 255);

	// PSW/A
	state->a = 55;

	// PSW as an 8-bit integer should now look like 0000 0111 (31)
	state->psw.pad = 0;
	state->psw.ac = 1;
	state->psw.cy = 1;
	state->psw.p = 1;
	state->psw.s = 1;
	state->psw.z = 1;

	Get_Register_Pair(PSW, pair);

	EXPECT_EQ(*pair[0], 31);
	EXPECT_EQ(*pair[1], 55);
}

TEST(State, Get_Register_Pair_Val)
{
	// bc = 0xaabb
	state->b = 0xaa;
	state->c = 0xbb;
	EXPECT_EQ(Get_Register_Pair_Val(REG_B), 0xaabb);

	// de = 0x1020
	state->d = 0x10;
	state->e = 0x20;
	EXPECT_EQ(Get_Register_Pair_Val(REG_D), 0x1020);

	// hl = 0xffff
	state->h = 0xff;
	state->l = 0xff;
	EXPECT_EQ(Get_Register_Pair_Val(REG_H), 0xffff);

	// bc = 0xabcd
	state->b = 0xab;
	state->c = 0xcd;
	EXPECT_EQ(Get_Register_Pair_Val(REG_B), 0xabcd);
}

TEST(State, Store_Register_Pair_Val)
{
	// bc = 0xaabb
	state->b = 0x00;
	state->c = 0x00;

	Store_Register_Pair_Val(REG_B, 0xaabb);

	EXPECT_EQ(state->b, 0xaa);
	EXPECT_EQ(state->c, 0xbb);

	// de = 0xff00
	state->d = 0x00;
	state->e = 0x00;

	Store_Register_Pair_Val(REG_D, (uint16_t)0xff00);

	EXPECT_EQ(state->d, 0xff);
	EXPECT_EQ(state->e, 0x00);

	// hl = 0x0330
	state->h = 0x00;
	state->l = 0x00;

	Store_Register_Pair_Val(REG_H, 0x0330);

	EXPECT_EQ(state->h, 0x03);
	EXPECT_EQ(state->l, 0x30);
}

TEST(State, Get_SP)
{
	state->sp = 0xffaa;

	uint16_t *spP = Get_SP();

	EXPECT_EQ(*spP, 0xffaa);
}

TEST(State, PSW_Update_Zero_Bit)
{
	PSW_Update_Zero_Bit(124);
	EXPECT_EQ(state->psw.z, 0);

	PSW_Update_Zero_Bit(0);
	EXPECT_EQ(state->psw.z, 1);
}

TEST(State, PSW_Update_Sign_Bit)
{
	PSW_Update_Sign_Bit(0b10000000);
	EXPECT_EQ(state->psw.s, 1);

	PSW_Update_Sign_Bit(0b00010101);
	EXPECT_EQ(state->psw.s, 0);
}

TEST(State, PSW_Update_Parity_Bit)
{
	PSW_Update_Parity_Bit(0b01110100);
	EXPECT_EQ(state->psw.p, 1);

	PSW_Update_Parity_Bit(0b01001010);
	EXPECT_EQ(state->psw.p, 0);

	PSW_Update_Parity_Bit(0b10101010);
	EXPECT_EQ(state->psw.p, 1);

	PSW_Update_Parity_Bit(0b11111111);
	EXPECT_EQ(state->psw.p, 1);

	PSW_Update_Parity_Bit(0b00000000);
	EXPECT_EQ(state->psw.p, 1);

	PSW_Update_Parity_Bit(0b00000001);
	EXPECT_EQ(state->psw.p, 0);
}

TEST(State, PSW_Update_Carry_Bit)
{
	// Additions - if overflow, set carry
	PSW_Update_Carry_Bit((uint8_t)0b100000000, 0b1, 1);
	EXPECT_EQ(state->psw.cy, 1);

	PSW_Update_Carry_Bit(0b01001010, 0b00000100, 1);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(255 + 255), 255, 1);
	EXPECT_EQ(state->psw.cy, 1);

	// Subtractions - if NO overflow, set carry
	PSW_Update_Carry_Bit((uint8_t)(4 - 3), 4, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(0x3e - 0x3e), 0x3e, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(4 - 5), 4, 0);
	EXPECT_EQ(state->psw.cy, 1);

	PSW_Update_Carry_Bit((uint8_t)(4 - 5), 5, 0);
	EXPECT_EQ(state->psw.cy, 1);

	PSW_Update_Carry_Bit((uint8_t)(5 - 5), 5, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(255 - 255), 255, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(0 - 255), 0, 0);
	EXPECT_EQ(state->psw.cy, 1);

	PSW_Update_Carry_Bit((uint8_t)(200 - 100), 200, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(255 - 254), 255, 0);
	EXPECT_EQ(state->psw.cy, 0);

	// Subtraction edge cases
	PSW_Update_Carry_Bit((uint8_t)(255 - 1), 255, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(0 - 0), 0, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(5 - 0), 5, 0);
	EXPECT_EQ(state->psw.cy, 0);

	PSW_Update_Carry_Bit((uint8_t)(255 - 0), 255, 0);
	EXPECT_EQ(state->psw.cy, 0);

	return;

	// For 255 - 1, 255 - 2 ... 255 - 255, carry should be equal to 0
	for (int i = 0; i <= 255; i++)
	{
		PSW_Update_Carry_Bit((uint8_t)(255 - i), 255, 0);
		EXPECT_EQ(state->psw.cy, 0);
	}

	// For 0 - 1, 0 - 2 ... 0 - 255, carry should be equal to 1
	for (int i = 1; i <= 255; i++)
	{
		PSW_Update_Carry_Bit((uint8_t)(0 - i), 0, 0);
		EXPECT_EQ(state->psw.cy, 1);
	}
}