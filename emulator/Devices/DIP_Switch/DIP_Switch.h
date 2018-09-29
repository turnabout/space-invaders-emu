// 
// DIP Switch
// Used to set certain options/modes used by the program.
// 

#include <stdint.h>
#include "../../Export.h"

enum Switches {
	Switch_Unk0,
	Switch_Unk1,
	Switch_Unk2,
	Switch_Ships_Amount_1,
	Switch_Unk3,
	Switch_Ships_Amount_2,
	Switch_Extra_Ship,
	Switch_Coin_Info_Display
};

typedef struct DIP_Switch {
	uint8_t a: 1; // 0: ?
	uint8_t b: 1; // 1: ?
	uint8_t c: 1; // 2: ?
	uint8_t d: 1; // 3: 00 = 3 ships 10 = 5 ships
	uint8_t e: 1; // 4: Value read at power up?
	uint8_t f: 1; // 5: 01 = 4 ships 11 = 6 ships
	uint8_t g: 1; // 6: 0 = extra ship at 1500, 1 = extra ship at 1000 
	uint8_t h: 1; // 7: Coin info displayed in demo screen, 0 = ON
} DIP_Switch;

// Set a DIP Switch value - n being the nth switch to set value to.
EXPORT void Set_Switch_Val(uint8_t n, uint8_t val);

// Get DIP Switch value stored at n.
EXPORT uint8_t Get_Switch_Val(uint8_t n);