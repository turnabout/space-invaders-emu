#include "pch.h"

extern "C" {
	#include "../emulator/State.h"
}

#pragma comment(lib, "../Debug/emulator.lib")

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