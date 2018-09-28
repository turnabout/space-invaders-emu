// 
// Device representing the user controls
// Gets the current state of the controls. Binds to keyboard state.
// 

#include <stdint.h>

// Gets the current state of the given control; 1 if active, 0 if inactive.
// Given argument must be a member of below Control_State_Bits enumeration.
uint8_t Get_Control_State(uint8_t control);

// Enumerating what each control state bit stands for
enum Controls_State_Bits {
	ControlState_P1_Start,
	ControlState_P1_Shot,
	ControlState_P1_Left,
	ControlState_P1_Right,
	ControlState_P2_Start,
	ControlState_P2_Shot,
	ControlState_P2_Left,
	ControlState_P2_Right,
	ControlState_Tilt,
	ControlState_Credit
};