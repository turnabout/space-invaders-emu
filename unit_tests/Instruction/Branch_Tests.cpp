#include "pch.h"
#include "../unit_tests.h"

TEST(Branch, JMP)
{
	// Jump to 0x04ef
	JMP(0x04, 0xef);
	EXPECT_EQ(state->pc, 0x04ef);
}

TEST(Branch, JNZ)
{
	// Jump to 0x02ff if Zero bit = 0
	state->pc = 0x0000;
	state->psw.z = 1;
	JNZ(0x02, 0xff);
	EXPECT_EQ(state->pc, 0x0000);

	state->pc = 0x0000;
	state->psw.z = 0;
	JNZ(0x03, 0xe3);
	EXPECT_EQ(state->pc, 0x03e3);
}

TEST(Branch, RST)
{
	RST(0);
	EXPECT_EQ(state->pc, 0);

	RST(1);
	EXPECT_EQ(state->pc, 8);

	RST(2);
	EXPECT_EQ(state->pc, 16);

	RST(7);
	EXPECT_EQ(state->pc, 56);
}