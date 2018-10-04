#include <windows.h>
#include <tchar.h>
#include <stdint.h>

#include "WinAPI.h"

#define BYTES_PER_ROW  32
#define TOTAL_ROWS     224

// Pixels color when on/off
//                        rrggbb
#define PIXEL_ON_COLOR  0xff0000
#define PIXEL_OFF_COLOR 0x0000ff

// Sent interrupts opcodes
#define BYTE_RST1 0xcf
#define BYTE_RST2 0xd7

// Window support
static TCHAR szWindowClass[] = _T("EmuApp");
static TCHAR szTitle[]       = _T("Emulator");
static MSG msg;
static HWND window;

// Interrupt support
static uint8_t interruptToSend = 0x00;
static uint8_t interruptN = 0;
static int timerUpdateTimeMs = 250; // The interrupt timer's update time, in ms

// Draw support
static BITMAPINFO *bmInfo;
static uint8_t *vram;
static uint8_t *vramRotated;

void Draw();

void CALLBACK Timer_Callback(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	// Draw screen when timer goes off and set interrupt to be sent
	Draw();
	
	// Set interrupt to be sent
	interruptToSend = (interruptN) ? BYTE_RST1 : BYTE_RST2;
	interruptN ^= 1;
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

int CreateEmulatorWindow(int winWidth, int winHeight)
{
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
		winWidth, winHeight,
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

void Initialize_Display(uint8_t *vramParam)
{
	// Store vram
	vram = vramParam;

	// Store bitmap info
	WORD bmInfoSize = sizeof(BITMAPINFOHEADER) + (2 * sizeof(RGBQUAD));
	bmInfo = (BITMAPINFO *)malloc(bmInfoSize);

    ZeroMemory(bmInfo, sizeof(bmInfoSize));

    bmInfo->bmiHeader.biBitCount    = 1;
     bmInfo->bmiHeader.biWidth       = 256;  // TODO: un-hardcode
     bmInfo->bmiHeader.biHeight      = 224; // TODO: un-hardcode
    //bmInfo->bmiHeader.biWidth       = 224;     // TODO: un-hardcode
    //bmInfo->bmiHeader.biHeight      = -256;    // TODO: un-hardcode

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

	// Display to screen immediately
	Draw();
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

void Draw()
{
    HDC dc = GetDC(window);

	// 32 bytes (256 bits/pixels) per row
    StretchDIBits(
        dc,
        0, 0, 256, 224, // Destination (x, y, w, h)
        0, 0, 256, 224, // Source (x, y, w, h)
        vram, // VRAM to read from
        bmInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    ReleaseDC(window, dc);
}