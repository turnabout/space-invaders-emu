#include "pch.h"
#include "unit_tests.h"

// Use module's State across all tests
State8080 *state = Get_State();

TEST(State, Reset_State_Test)
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

TEST(State, Get_Reg_Address)
{
	state->a = 0x0a;
	state->b = 0x0b;
	state->d = 0x0d;
	state->l = 0x0f;

	uint8_t *regA = Get_Reg_Address(REG_A);
	uint8_t *regB = Get_Reg_Address(REG_B);
	uint8_t *regD = Get_Reg_Address(REG_D);
	uint8_t *regL = Get_Reg_Address(REG_L);

	EXPECT_EQ(*regA, 0x0a);
	EXPECT_EQ(*regB, 0x0b);
	EXPECT_EQ(*regD, 0x0d);
	EXPECT_EQ(*regL, 0x0f);

	Reset_State();
}

TEST(State, PSW_Update_Sign_Bit)
{
	PSW_Update_Sign_Bit(0b10000000);
	EXPECT_EQ(state->psw.s, 1);

	PSW_Update_Sign_Bit(0b00010101);
	EXPECT_EQ(state->psw.s, 0);
}

TEST(State, PSW_Update_Zero_Bit)
{
	PSW_Update_Zero_Bit(124);
	EXPECT_EQ(state->psw.z, 0);

	PSW_Update_Zero_Bit(0);
	EXPECT_EQ(state->psw.z, 1);
}