#include "pch.h"
#include "../unit_tests.h"

TEST(Instructions_Arithmetic, ADD)
{
	state->a = 0xa;

	EXPECT_EQ(0xa, state->a);
}