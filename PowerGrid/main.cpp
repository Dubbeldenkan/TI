#include "Windows.h"
#include "Game.h"

LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM
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

void InitWinMain(HINSTANCE hInst, char winName[])
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = MsgProc;
	wc.hInstance = hInst;
	wc.lpszClassName = winName;
	RegisterClass(&wc);
}

HWND InitWindow(HINSTANCE hInst, char winName[])
{
	InitWinMain(hInst, winName);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 1, 1, 1300, 670 };
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
		hInst,
		NULL);

	return hWnd;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	char windowName[] = "Power Grid";
	HWND hWnd = InitWindow(hInstance, windowName);

	//Graphics* graphics = new Graphics(hWnd);

	//Image image = graphics->LoadImage("USA.png");

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	Board *board = new Board(true, true, true, false, false, false, "USAPowerGrid.png");
	Game *game = new Game(6, board, hWnd);

	// Main message loop:
	MSG msg;
	bool isRunning = true;
	while(true)
	{
		game->RunTurn();
		/*graphics->StartDrawing();
		graphics->Draw(&image, 100, 0, 0.5);
		graphics->StopDrawing();
		graphics->Flip();*/
		MSG msg = { 0 };
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//graphics->Flip();
		}
		Sleep(10);
	}
	return 0;
}