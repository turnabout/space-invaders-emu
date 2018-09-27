#include "pch.h"
#include "unit_tests.h"

TEST(Number_Helpers, uint8_To_uint16)
{
	EXPECT_EQ(uint8_To_uint16(0xaa, 0xbb), 0xaabb);
	EXPECT_EQ(uint8_To_uint16(0x12, 0x34), 0x1234);
	EXPECT_EQ(uint8_To_uint16(0xff, 0x00), 0xff00);
}