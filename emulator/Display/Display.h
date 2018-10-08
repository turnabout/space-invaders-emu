//
// WinAPI frontend for the emulator.
// Used to run the emulator in windows.
//

// Create and display the emulator window.
// Scale is the display's initial scale.
// Vram is a pointer to where the video ram begins.
int Init_Emulator_Display(int scale, uint8_t *vram);

// Handle the GUI. To be used inside the main loop.
// Returns 0 when the main window is closed.
int Handle_GUI();

// Check whether the display has generated an interrupt.
// Returns the number of the generated interrupt, if there was one.
// Otherwise, returns 0.
uint8_t Check_Display_Interrupt();

void Draw();