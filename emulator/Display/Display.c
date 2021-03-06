#include <windows.h>
#include <tchar.h>
#include <stdint.h>
#include <math.h>

#include "Display.h"
#include "Display_Helpers.h"

#define M_PI 3.14159265358979323846

// Pixels color when on/off
//                        rrggbb
#define PIXEL_ON_COLOR  0xffffff
#define PIXEL_OFF_COLOR 0x000000

// Sent interrupts opcodes
#define BYTE_RST1 0xcf
#define BYTE_RST2 0xd7

// When the interrupt was generated (one is sent when the "beam" is supposed
// to be at half screen, the other is sent at the start of VBLANK when the 
// beam is supposed to be at the bottom of the screen).
#define HALF_SCREEN   0
#define BOTTOM_SCREEN 1

// Original (un-rotated) screen dimensions
#define SCREEN_WIDTH  256
#define SCREEN_HEIGHT 224
#define VRAM_SIZE SCREEN_WIDTH * SCREEN_HEIGHT / 8

// Window support
static TCHAR szWindowClass[] = _T("SpaceInvadersEmu");
static TCHAR szTitle[]       = _T("Space Invaders Emu");
static MSG msg;
static HWND window;

// Interrupt support
static uint8_t interruptToSend = 0x00; // Current interrupt we're sending
static uint8_t interruptN = HALF_SCREEN; // Interrupt number (0/1)
static int timerUpdateTimeMs = 1000 / 120; // The interrupt timer's update time, in ms

// Draw support
static BITMAPINFO *bmInfo;
static HBITMAP frameBitmap;
static HDC dc;
static uint8_t *vram;
static uint8_t *vramInverted;
static int displayScale;

// When the interrupt timer goes off, set appropriate interrupt to be sent & 
// draw the current frame when necessary
void CALLBACK Timer_Callback(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	// Set interrupt to be sent, draw when VBLANK (bottom of screen) reached
	if (interruptN == HALF_SCREEN)
	{
		interruptToSend = BYTE_RST1;
	}
	else
	{
		interruptToSend = BYTE_RST2;
		Draw();
	}
	
	// Toggle interruptN between HALF_SCREEN & BOTTOM_SCREEN
	interruptN ^= BOTTOM_SCREEN;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// Adjust DC scale
void Adjust_Scale(int scale)
{
	XFORM xform;

	xform.eM11 = (FLOAT) scale;
	xform.eM12 = (FLOAT) 0.0;
	xform.eM21 = (FLOAT) 0.0;
	xform.eM22 = (FLOAT) scale;
	xform.eDx = (FLOAT) 0.0;
	xform.eDy = (FLOAT) 0.0;

	ModifyWorldTransform(dc, &xform, MWT_RIGHTMULTIPLY);
}

// Adjust DC rotation, rotating to show the display right-side up
void Adjust_Rotation()
{
	SetGraphicsMode(dc, GM_ADVANCED);

	// Rotate
	XFORM xform;
	double angle = 90 * (M_PI / 180);

	xform.eM11 = (FLOAT)cos(angle);
	xform.eM12 = (FLOAT)(-sin(angle));
	xform.eM21 = (FLOAT)sin(angle);
	xform.eM22 = (FLOAT)cos(angle);
	xform.eDx = 0;
	xform.eDy = SCREEN_WIDTH;
	SetWorldTransform(dc, &xform);
}

void Initialize_Display(uint8_t *vramParam)
{
	// Store vram
	vram = vramParam;

	// Store bitmap info
	WORD bmInfoSize = sizeof(BITMAPINFOHEADER) + (2 * sizeof(RGBQUAD));
	bmInfo = (BITMAPINFO *)malloc(bmInfoSize);

    ZeroMemory(bmInfo, sizeof(bmInfoSize));

    bmInfo->bmiHeader.biBitCount    = 1;
    bmInfo->bmiHeader.biWidth       = SCREEN_WIDTH;
    bmInfo->bmiHeader.biHeight      = -SCREEN_HEIGHT;
    bmInfo->bmiHeader.biPlanes      = 1;
    bmInfo->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmInfo->bmiHeader.biCompression = BI_RGB;

	// Set bmi colors
	bmInfo->bmiColors[0].rgbRed   = (PIXEL_OFF_COLOR >> 16) & 0xff;
	bmInfo->bmiColors[0].rgbGreen = (PIXEL_OFF_COLOR >> 8) & 0xff;
	bmInfo->bmiColors[0].rgbBlue  = PIXEL_OFF_COLOR & 0xff;

	bmInfo->bmiColors[1].rgbRed   = (PIXEL_ON_COLOR >> 16) & 0xff;
	bmInfo->bmiColors[1].rgbGreen = (PIXEL_ON_COLOR >> 8) & 0xff;
	bmInfo->bmiColors[1].rgbBlue  = PIXEL_ON_COLOR & 0xff;

    dc = GetDC(window);

	// Adjust screen
	Adjust_Rotation();
	Adjust_Scale(displayScale);

	// VRAM copy, holds vram with its bits inverted
	vramInverted = (uint8_t *)malloc((sizeof(uint8_t) * VRAM_SIZE) + 1);

	// Display to screen immediately
	Draw();
}


int Init_Emulator_Display(int scale, uint8_t *vram)
{
	displayScale = scale;

	WNDCLASSEX wcex;

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;  
	wcex.cbWndExtra    = 0;  
	wcex.hInstance     = GetModuleHandle(0);
	wcex.hIcon         = LoadIcon(0, IDI_APPLICATION);  
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);  
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	// Register
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(0, "Call to RegisterClassEx failed!", szTitle, 0);
		return 0;
	}

	// Create window
	window = CreateWindow(
		szWindowClass,
		szTitle,
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(scale * SCREEN_HEIGHT) + 16, (scale * SCREEN_WIDTH) + 38,
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL
	);

	if (!window)
	{
		MessageBox(0, "Call to CreateWindow failed!", "Test", 0);
		return 0;
	}

	// Show window
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);

	// Set the timer deciding when to draw & send interrupts
	SetTimer(NULL, 0, timerUpdateTimeMs, (TIMERPROC) &Timer_Callback);

	Initialize_Display(vram);

	return 1;
}

// Handles winapi messages. Returns 0 when exiting
int Handle_GUI()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Exit
		if (msg.message == WM_CLOSE || 
			msg.message == WM_QUIT  || 
			msg.message == WM_DESTROY)
		{
			return 0;
		}
	}

	return 1;
}

void EndGUI()
{
	DestroyWindow(window);
}

uint8_t Check_Display_Interrupt()
{
	if (interruptToSend)
	{
		uint8_t sentInt = interruptToSend;
		interruptToSend = 0;
		return sentInt;
	}

	return 0;
}

// Draw bitmap to dc
void Draw_Bitmap_To_DC(HBITMAP hBitmap, HDC hdc)
{
    BITMAP bm;
    HDC MemDC = CreateCompatibleDC(hdc);
    SelectObject(MemDC, hBitmap);
    GetObject(hBitmap, sizeof(bm), &bm);
    BitBlt(
		hdc, 
		0, 0, // Destination rectangle top-left X/Y
		bm.bmWidth, bm.bmHeight, // Destination & source rectangle W/H 
		MemDC, 
		0, 0, // Source rectangle top-left X/Y 
		SRCCOPY
	);
    DeleteDC(MemDC);
}

// Invert bits from vram. "from" is from where to invert all the bits, "to" is 
// where to store them.
void Invert_Vram(uint8_t *from, uint8_t *to)
{
	int i = VRAM_SIZE;

	while (i-- > 0)
	{
		*to = Invert_Bits(*from);
		from++;
		to++;
	}
}

// Draw the current frame from vram data
void Draw()
{
	// Invert all vram bits, store in vram copy
	// We need to invert because Windows API interprets them backwards to the 
	// way they are stored by the Space Invaders program
	Invert_Vram(vram, vramInverted);

	frameBitmap = CreateCompatibleBitmap(dc, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDIBits(dc, frameBitmap, 0,SCREEN_HEIGHT,vramInverted,bmInfo, DIB_RGB_COLORS);
	Draw_Bitmap_To_DC(frameBitmap, dc);
}