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