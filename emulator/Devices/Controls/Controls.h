// 
// Device representing the user controls
// Sends back the current state of the controls. Binds to the keyboard state
// 

#include <stdint.h>

// Gets the current state of the gameplay-related player controls.
// Returns a byte with each bit signifying the state of the associated control
// (0 when inactive, 1 when active). From LSB to MSB:
// Bit 0: 1P Start
// Bit 1: 1P Shot
// Bit 2: 1P Left
// Bit 3: 1P Right
// Bit 4: 2P Start
// Bit 5: 2P Shot
// Bit 6: 2P Left
// Bit 7: 2P Right
// Bit 8: Tilt
// Bit 9: Credit (1 if deposit)
// Other bits are unused
uint16_t Get_Controls_State();