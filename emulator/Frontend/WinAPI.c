#include <windows.h>
#include <tchar.h>

#include "WinAPI.h"

static TCHAR szWindowClass[] = _T("EmuApp");
static TCHAR szTitle[] = _T("Emulator");
static MSG msg;

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
	HWND window = CreateWindow(
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

	return 1;
}

int HandleGUI()
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