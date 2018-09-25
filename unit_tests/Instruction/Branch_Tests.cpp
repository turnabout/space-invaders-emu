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
}