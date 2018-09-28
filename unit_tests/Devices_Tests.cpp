#include "pch.h"
#include "unit_tests.h"

// Shift Hardware
TEST(Devices, Shift_Register)
{
	Reset_Shift_Register();

	// Initial value should be 0
	EXPECT_EQ(Read_Data(), 0x00);

	// Write to & read from
	Write_Data(0b11111111);
	EXPECT_EQ(Read_Data(), 0b11111111);

	// Newly written data shifts old data to the right
	Write_Data(0b00000000);
	EXPECT_EQ(Read_Data(), 0b00000000);

	// Setting offset to 1 changes the result like so:
	//  rrrrrrrr        
	// 0000000011111111
	Set_Offset(1);
	EXPECT_EQ(Read_Data(), 0b00000001);

	// Setting offset to 7:
	//        rrrrrrrr
	// 0000000011111111
	Set_Offset(7);
	EXPECT_EQ(Read_Data(), 0b01111111);

	Set_Offset(7);
}