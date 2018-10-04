#include <windows.h>

// Create and display the emulator window
int CreateEmulatorWindow(int winWidth, int winHeight);

// Handle the GUI, to be used inside the main loop.
// Returns 0 when the main window is closed.
int Handle_GUI();

// Initialize the display, making it usable for drawing.
void Initialize_Display(uint8_t *vram);

// Update the display as necessary.
// Returns the number of the generated interrupt, if there was one.
// Otherwise, returns 0.
uint8_t Check_Display_Interrupt();
void Draw();