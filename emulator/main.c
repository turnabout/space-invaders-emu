#include <stdio.h>
#include "State.h"

int main(int argc, char *argv[])
{
	printf("Should be A: %02x\n", *Get_Reg_Address(REG_A));
	printf("Should be B: %02x\n", *Get_Reg_Address(REG_B));
	printf("Should be C: %02x\n", *Get_Reg_Address(REG_C));
	printf("Should be 77 (L): %02x\n", *Get_Reg_Address(REG_L));

	getchar();
}