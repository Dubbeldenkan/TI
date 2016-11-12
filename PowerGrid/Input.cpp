#include "Input.h"

Game* Input::_game;
Draw::Pos Input::_mousePos = Draw::Pos(0, 0);

Input::Input()
{}

void Input::SetGame(Game* game)
{
	_game = game;
}

void Input::MouseClick()
{
	if (_game->GetCurrentPhase() == 2 && _game->GetCurrentSubPhase() == Game::choosePowerPlant)
	{
		int plantPos = CheckPowerPlantPos();
		if (plantPos > 0)
		{
			_game->GetPlayerInTurn()->SetSelectedPowerPlant(plantPos);
		}
	}
}

int Input::CheckPowerPlantPos()
{
	int result = 0;
	bool xPosForMostLeft = (_mousePos.x > _game->GetDraw()->GetFirstCurrentPlantPos().x) &&
		(_mousePos.x < (_game->GetDraw()->GetFirstCurrentPlantPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x));

	bool xPosForMiddle = (_mousePos.x > 
		(_game->GetDraw()->GetFirstCurrentPlantPos().x + _game->GetDraw()->GetPlantDiff().x)) &&
		(_mousePos.x < (_game->GetDraw()->GetFirstCurrentPlantPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x +
			_game->GetDraw()->GetPlantDiff().x));

	bool xPosForMostRight = (_mousePos.x >
		(_game->GetDraw()->GetFirstCurrentPlantPos().x + 2*_game->GetDraw()->GetPlantDiff().x)) &&
		(_mousePos.x < (_game->GetDraw()->GetFirstCurrentPlantPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x +
			2*_game->GetDraw()->GetPlantDiff().x));

	bool yPosForUpper = (_mousePos.y > _game->GetDraw()->GetFirstCurrentPlantPos().y) &&
		(_mousePos.y < (_game->GetDraw()->GetFirstCurrentPlantPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y));

	bool yPosForLower = (_mousePos.y >
		(_game->GetDraw()->GetFirstCurrentPlantPos().y + _game->GetDraw()->GetPlantDiff().y)) &&
		(_mousePos.y < (_game->GetDraw()->GetFirstCurrentPlantPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y +
			_game->GetDraw()->GetPlantDiff().y));

	if(xPosForMostLeft)
	{
		if (yPosForUpper)
		{
			result = 1;
		}
		else if (yPosForLower && (_game->GetCurrentStep() != 3))
		{
			result = 3;
		}
		else if (yPosForLower && (_game->GetCurrentStep() == 3))
		{
			result = 4;
		}
	}
	if (xPosForMiddle)
	{
		if (yPosForUpper)
		{
			result = 2;
		}
		else if (yPosForLower && (_game->GetCurrentStep() != 3))
		{
			result = 4;
		}
		else if (yPosForLower && (_game->GetCurrentStep() == 3))
		{
			result = 5;
		}
	}

	if (xPosForMostRight && (_game->GetCurrentStep() == 3))
	{
		if (yPosForUpper)
		{
			result = 3;
		}
		else if (yPosForLower)
		{
			result = 6;
		}
	}
	return result;
}

LRESULT CALLBACK Input::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM
	lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		MouseClick();
		break;
	}
	case WM_MOUSEMOVE:
	{
		_mousePos.x = LOWORD(lParam);
		_mousePos.y = HIWORD(lParam);
		break;
	}
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
		winName,
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