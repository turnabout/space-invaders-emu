#include <stdio.h>

#include "State.h"
#include "Emulator/Emulator.h"
#include "Instructions/Instructions.h"

extern struct State8080 state;

int main(int argc, char *argv[])
{
	Init_Memory("../../invaders/invaders");

	uint8_t a = Get_Rom_Byte(0x1FF0);

	printf("%02x\n", a);

	getchar();
}