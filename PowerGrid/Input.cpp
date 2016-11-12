#include "Input.h"

Input::Input()
{
	/*HWND hwndMain = CreateWindow(
		"MinF�nsterKlass",
		"Ett vanligt f�nster...",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 400,
		0, 0, hInstance, 0);
	...d�refter skapar vi knappen som ska ligga i f�nstret :*/
	/*HWND myButton = CreateWindow(
		"BUTTON", // F�nsterklass
		"Klicka p� mig!", // Text p� knappen
		WS_CHILD | WS_VISIBLE, // Stil, OBS: WS_CHILD
		10, 20, // Position, relativt f�r�ldern
		150, 40, // Storlek
		hwndMain, // F�r�lderf�nstrets handtag
		(HMENU)MYBUTTON_ID, // Knappens ID
		hInstance, // HINSTANCE som skickas med i WinMain
		0); // Avancerat, s�tt till NULL*/
}

LRESULT CALLBACK Input::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM
	lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, 0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void InitWinMain(HINSTANCE* hInst, char winName[], Input* input)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = input->MsgProc;
	wc.hInstance = *hInst;
	wc.lpszClassName = winName;
	RegisterClass(&wc);
}

HWND InitWindow(HINSTANCE* hInst, char winName[], Input* input)
{
	InitWinMain(hInst, winName, input);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 1, 1, 1300, 660 };
	AdjustWindowRect(&windowRect, windowStyle, false);
	HWND hWnd = CreateWindow(
		winName,
		"Direct3D",
		windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		*hInst,
		NULL);

	return hWnd;
}