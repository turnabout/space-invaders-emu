#include <windows.h>
#include "Controls.h"

#define KEYBINDINGS_AMOUNT 10

static char keyBindings[KEYBINDINGS_AMOUNT] = {
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

uint16_t Get_Controls_State()
{
	uint16_t state = 0x0000;

	// Gather all control states
	for (int i = 0; i < KEYBINDINGS_AMOUNT; i++)
	{
		// Allign key state's "active" bit with currently looped state bit
		state |= (
			((uint16_t)GetKeyState(keyBindings[i]) >> 15) << i
		);
	}

	return state;
}