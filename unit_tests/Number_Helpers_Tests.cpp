#include "pch.h"
#include "unit_tests.h"

TEST(Number_Helpers, Bytes_To_Short)
{
	EXPECT_EQ(Bytes_To_Short(0xaa, 0xbb), 0xaabb);
	EXPECT_EQ(Bytes_To_Short(0x12, 0x34), 0x1234);
	EXPECT_EQ(Bytes_To_Short(0xff, 0x00), 0xff00);
}