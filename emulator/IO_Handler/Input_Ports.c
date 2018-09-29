#include "IO_Handler.h"

uint8_t Read_Input_Port_0()
{
	return 0b11110000;
}

uint8_t Read_Input_Port_1()
{
	return Get_Control_State(ControlState_Credit) |
		(Get_Control_State(ControlState_P2_Start) << 1) |
		(Get_Control_State(ControlState_P1_Start) << 2) |
		(1 << 3) |
		(Get_Control_State(ControlState_P1_Shot) << 4) |
		(Get_Control_State(ControlState_P1_Left) << 5) |
		(Get_Control_State(ControlState_P1_Right) << 6);
}

uint8_t Read_Input_Port_2()
{
	return Get_Switch_Val(Switch_Ships_Amount_1) |
		(Get_Switch_Val(Switch_Ships_Amount_2) << 1) |
		(Get_Control_State(ControlState_Tilt) << 2) |
		(Get_Switch_Val(Switch_Extra_Ship) << 3) |
		(Get_Control_State(ControlState_P2_Shot) << 4) |
		(Get_Control_State(ControlState_P2_Left) << 5) |
		(Get_Control_State(ControlState_P2_Right) << 6) |
		(Get_Switch_Val(Switch_Coin_Info_Display) << 7);
}

uint8_t Read_Input_Port_3()
{
	return Read_Shift_Register_Data();
}