#include "pch.h"
#include "unit_tests.h"

// Shift Hardware
TEST(Devices, Shift_Register)
{
	Reset_Shift_Register();

	// Initial value should be 0
	EXPECT_EQ(Read_Shift_Register_Data(), 0x00);

	// Write to & read from
	Write_Shift_Register_Data(0b11111111);
	EXPECT_EQ(Read_Shift_Register_Data(), 0b11111111);

	// Newly written data shifts old data to the right
	Write_Shift_Register_Data(0b00000000);
	EXPECT_EQ(Read_Shift_Register_Data(), 0b00000000);

	// Setting offset to 1 changes the result like so:
	//  rrrrrrrr        
	// 0000000011111111
	Set_Offset(1);
	EXPECT_EQ(Read_Shift_Register_Data(), 0b00000001);

	// Setting offset to 7:
	//        rrrrrrrr
	// 0000000011111111
	Set_Offset(7);
	EXPECT_EQ(Read_Shift_Register_Data(), 0b01111111);

	Set_Offset(7);
}

TEST(Devices, DIP_Switch)
{
	// Auto test all 8 switches
	for (int i = 0; i < 8; i++)
	{
		Set_Switch_Val(i, 1);
		EXPECT_EQ(Get_Switch_Val(i), 1);

		Set_Switch_Val(i, 0);
		EXPECT_EQ(Get_Switch_Val(i), 0);
	}
}