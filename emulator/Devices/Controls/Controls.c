#include <windows.h>
#include "Controls.h"

static char keyBindings[10] = {
	VK_RETURN, // 1P Start
	VK_SPACE,  // 1P Shot
	VK_LEFT,   // 1P Left
	VK_RIGHT,  // 1P Right
	'S',       // 2P Start
	'F',       // 2P Shot
	'Z',       // 2P Left
	'C',       // 2P Right
	VK_UP,     // Tilt
	VK_DOWN,   // Credit
};

uint8_t Get_Control_State(uint8_t control)
{
	return (uint16_t)GetKeyState(keyBindings[control]) >> 15;
}