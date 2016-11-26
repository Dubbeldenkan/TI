#include "Game.h"
#include "Input.h"
#include "ManageAI.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	char windowName[] = "Power Grid";
	Input* input = new Input();

	HWND hWnd = InitWindow(&hInstance, windowName, input);

	int numberOfPlayers = 3;
	Game *game = new Game(numberOfPlayers, hWnd);
	
	input->SetGame(game);
	ManageAI* manageAI = new ManageAI(game, game->GetPlayerVector());

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	bool isRunning = true;
	while(true)
	{
		game->Run();
		manageAI->DoAction();
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
		}
		Sleep(10);
	}
	return 0;
}