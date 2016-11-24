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
	if (!_game->GetPlayerInTurn()->GetHumanPlayer())
	{
		//Do nothing
	}
	else if (PassedBeenPressed())
	{
		_game->GetPlayerInTurn()->SetPassed();
	}
	else if (_game->GetCurrentPhase() == 2)
	{
		switch (_game->GetCurrentSubPhase())
		{
		case Game::choosePowerPlant:
		{
			int plantPos = CheckPowerPlantPos();
			if ((plantPos > 0) &&
				(_game->GetPowerPlantMarket()->GetPowerPlantCurrentDeck(plantPos - 1)->GetPowerPlantNumber()
					<= _game->GetPlayerInTurn()->GetAmountOfElektro()))
			{
				_game->GetPlayerInTurn()->SetSelectedPowerPlant(plantPos);
			}
			break;
		}
		case Game::bid:
		{
			if (IncreaseBidPressed())
			{
				_game->IncreaseNextBid(1);
			}
			else if (DecreaseBidPressed())
			{
				_game->IncreaseNextBid(-1);
			}
			else if (BidPressed())
			{
				_game->GetPlayerInTurn()->SetBid(_game->GetBidForSelectedPowerPlant());
			}
			break;
		}
		case  Game::placePowerPlant:
		{
			int tempPowerPlantPos = PowerPlantPressed();
			if (tempPowerPlantPos > -1)
			{
				_game->GetPlayerInTurn()->SetNewPowerPlantPos(tempPowerPlantPos);
			}
			break;
		}
		}
	}
	else if (_game->GetCurrentPhase() == 3)
	{
		int coalNumber = GetResourcePressed(ResourceMarket::coal);
		int oilNumber = GetResourcePressed(ResourceMarket::oil);
		int garbageNumber = GetResourcePressed(ResourceMarket::garbage);
		int uranNumber = GetResourcePressedForUran();
		if (coalNumber > 0)
		{
			int cost = _game->GetResourceMarket()->GetCost(coalNumber, ResourceMarket::coal);
			_game->GetPlayerInTurn()->SetBuyResourceStruct(ResourceMarket::coal, coalNumber, cost);
		}
		else if (oilNumber > 0)
		{
			int cost = _game->GetResourceMarket()->GetCost(oilNumber, ResourceMarket::oil);
			_game->GetPlayerInTurn()->SetBuyResourceStruct(ResourceMarket::oil, oilNumber, cost);
		}
		else if (garbageNumber > 0)
		{
			int cost = _game->GetResourceMarket()->GetCost(garbageNumber, ResourceMarket::garbage);
			_game->GetPlayerInTurn()->SetBuyResourceStruct(ResourceMarket::garbage, garbageNumber, cost);
		}
		else if (uranNumber > 0)
		{
			int cost = _game->GetResourceMarket()->GetCost(uranNumber, ResourceMarket::uranium);
			_game->GetPlayerInTurn()->SetBuyResourceStruct(ResourceMarket::uranium, uranNumber, cost);
		}
	}
	else if (_game->GetCurrentPhase() == 4)
	{
		char* cityName = GetPressedCityName();
		if (strcmp(cityName, "") > 0)
		{
			_game->GetPlayerInTurn()->SetBuyCityStruct(cityName);
		}
	}
	else if (_game->GetCurrentPhase() == 5)
	{
		int tempPowerPlantPos = PowerPlantPressed();
		PowerPlant::EnergySource resourceType = _game->GetPlayerInTurn()->GetPowerPlant(tempPowerPlantPos)->GetType();
		int consumptionForPowerPlant = _game->GetPlayerInTurn()->GetPowerPlant(tempPowerPlantPos)->GetPowerPlantConsumption();
		if ((tempPowerPlantPos > -1) && 
			((_game->GetPlayerInTurn()->GetAmountOfResource(resourceType) >= consumptionForPowerPlant) || 
			(resourceType == PowerPlant::coalOrOil && (_game->GetPlayerInTurn()->GetAmountOfResource(PowerPlant::coal) + 
				_game->GetPlayerInTurn()->GetAmountOfResource(PowerPlant::oil)) >= consumptionForPowerPlant) ||
				_game->GetPlayerInTurn()->GetPowerPlant(tempPowerPlantPos)->GetActive()))
		{
			_game->GetPlayerInTurn()->SetPowerPlantClicked(tempPowerPlantPos);
		}
	}
}

char* Input::GetPressedCityName()
{
	Board* board = _game->GetBoard();
	char* result = "";
	typedef std::map<std::string, City*>::iterator it_type;
	for (it_type it = board->GetCityDictFirstIterator(); it != board->GetCityDictLastIterator(); it++)
	{
		City* tempCity = it->second;
		bool xPosTrue = (_mousePos.x > tempCity->GetXPos()) &&
			(_mousePos.x < (tempCity->GetXPos() + _game->GetDraw()->GetSizeOfCity().x));
		bool yPosTrue = (_mousePos.y > tempCity->GetYPos()) &&
			(_mousePos.y < (tempCity->GetYPos() + _game->GetDraw()->GetSizeOfCity().y));
		if (board->CityIsInUsedRegion(tempCity) && xPosTrue && yPosTrue)
		{
			result = tempCity->GetName();
			break;
		}
	}
	return result;
}

int Input::GetResourcePressed(ResourceMarket::Resource resource)
{
	Draw* d = _game->GetDraw();
	Draw::Pos firstPos = Draw::Pos(0,0);
	Draw::Pos resourceDiff = d->GetResourceDiff();
	int maxAmountOfResources = ResourceMarket::MAX_AMOUNT_RESOURCE;
	int numberOfResources;
	int result = 0;
	switch (resource)
	{
	case ResourceMarket::coal:
		firstPos = d->GetFirstCoalPos();
		numberOfResources = _game->GetResourceMarket()->GetAmountOfCoal();
		break;
	case ResourceMarket::oil:
		firstPos = d->GetFirstOilPos();
		numberOfResources = _game->GetResourceMarket()->GetAmountOfOil();
		break;
	case ResourceMarket::garbage:
		firstPos = d->GetFirstGarbagePos();
		numberOfResources = _game->GetResourceMarket()->GetAmountOfGarbage();
		break;
	default:
		break;
	}
	for(int index = 0; index < maxAmountOfResources; index++)
	{
		bool xPosTrue = (_mousePos.x >(firstPos.x + resourceDiff.x*index) &&
			(_mousePos.x < (firstPos.x + resourceDiff.x*index + d->GetSizeOfResource().x)));
		bool yPosTrue = ((_mousePos.y > firstPos.y) &&
			(_mousePos.y < (firstPos.y + d->GetSizeOfResource().y)));
		if (xPosTrue && yPosTrue)
		{
			result = (index + 1) - (maxAmountOfResources - numberOfResources);
			result = max(0, result);
			break;
		}
	}
	return result;
}

int Input::GetResourcePressedForUran()
{
	Draw* d = _game->GetDraw();
	Draw::Pos firstPos = d->GetFirstUranPos();
	Draw::Pos resourceDiff = d->GetUranDiff();
	int maxAmountOfResources = ResourceMarket::MAX_AMOUNT_URAN;
	int numberOfResources = _game->GetResourceMarket()->GetAmountOfUran();
	int result = 0;
	for (int index = 0; index < maxAmountOfResources; index++)
	{
		bool xPosTrue;
		bool yPosTrue;
		if (index > 7)
		{
			xPosTrue = (_mousePos.x > (firstPos.x + resourceDiff.x * 8 + resourceDiff.x / 2 * ((index - 8) % 2)) &&
				(_mousePos.x < (firstPos.x + resourceDiff.x * 8 + resourceDiff.x / 2 * ((index - 8) % 2) +
					d->GetSizeOfResource().x)));
			yPosTrue = (_mousePos.y > (firstPos.y + resourceDiff.y*min(0, max(-1, index - 10))) &&
				(_mousePos.y < (firstPos.y + resourceDiff.y*min(0, max(-1, index - 10)) + d->GetSizeOfResource().y)));
		}
		else
		{
			xPosTrue = (_mousePos.x > (firstPos.x + resourceDiff.x*index) &&
				(_mousePos.x < (firstPos.x + resourceDiff.x*index + d->GetSizeOfResource().x)));
			yPosTrue = ((_mousePos.y > firstPos.y) &&
				(_mousePos.y < (firstPos.y + d->GetSizeOfResource().y)));
		}
		if (xPosTrue && yPosTrue)
		{
			result = (index + 1) - (maxAmountOfResources - numberOfResources);
			result = max(0, result);
			break;
		}
	}
	return result;
}

int Input::PowerPlantPressed()
{
	int powerPlantNumber = -1;
	int firstPowerPlantPosX = _game->GetDraw()->GetFirstPlayerPos().x + 
		_game->GetDraw()->GetFirstPlayerPowerPlantPos().x;
	int powerPlantDiffX = _game->GetDraw()->GetPlayerPowerPlantDiff().x;

	int firstPowerPlantPosY = _game->GetDraw()->GetFirstPlayerPos().y + 
		_game->GetDraw()->GetPlayerDiff().y*_game->GetPlayerInTurnPosition() +
		_game->GetDraw()->GetFirstPlayerPowerPlantPos().y;
	for (int index = 0; index < Player::numberOfPowerPlants; index++)
	{
		
		bool xPosTrue = (_mousePos.x > (firstPowerPlantPosX + powerPlantDiffX*index) &&
			(_mousePos.x < (firstPowerPlantPosX + powerPlantDiffX*index + _game->GetDraw()->GetSizeOfPowerPlant().x)));

		bool yPosTrue = (_mousePos.y >
			(firstPowerPlantPosY) &&
			(_mousePos.y < (firstPowerPlantPosY + _game->GetDraw()->GetSizeOfPowerPlant().y)));
		if (xPosTrue && yPosTrue)
		{
			powerPlantNumber = index;
			break;
		}
	}
	return powerPlantNumber;
}

bool Input::PassedBeenPressed()
{
	bool xPosTrue = (_mousePos.x > _game->GetDraw()->GetPassButtonPos().x) &&
		(_mousePos.x < (_game->GetDraw()->GetPassButtonPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x));

	bool yPosTrue = (_mousePos.y >
		(_game->GetDraw()->GetPassButtonPos().y ) &&
		(_mousePos.y < (_game->GetDraw()->GetPassButtonPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y)));
	return xPosTrue && yPosTrue;
}

bool Input::IncreaseBidPressed()
{
	bool xPosTrue = (_mousePos.x > _game->GetDraw()->GetIncreaseBidButtonPos().x) &&
		(_mousePos.x < (_game->GetDraw()->GetIncreaseBidButtonPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x));

	bool yPosTrue = (_mousePos.y >
		(_game->GetDraw()->GetIncreaseBidButtonPos().y) &&
		(_mousePos.y < (_game->GetDraw()->GetIncreaseBidButtonPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y)));
	return xPosTrue && yPosTrue;
}

bool Input::DecreaseBidPressed()
{
	bool xPosTrue = (_mousePos.x > _game->GetDraw()->GetDecreaseBidButtonPos().x) &&
		(_mousePos.x < (_game->GetDraw()->GetDecreaseBidButtonPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x));

	bool yPosTrue = (_mousePos.y >
		(_game->GetDraw()->GetDecreaseBidButtonPos().y) &&
		(_mousePos.y < (_game->GetDraw()->GetDecreaseBidButtonPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y)));
	return xPosTrue && yPosTrue;
}

bool Input::BidPressed()
{
	bool xPosTrue = (_mousePos.x > _game->GetDraw()->GetBidButtonPos().x) &&
		(_mousePos.x < (_game->GetDraw()->GetBidButtonPos().x + _game->GetDraw()->GetSizeOfPowerPlant().x));

	bool yPosTrue = (_mousePos.y >
		(_game->GetDraw()->GetBidButtonPos().y) &&
		(_mousePos.y < (_game->GetDraw()->GetBidButtonPos().y + _game->GetDraw()->GetSizeOfPowerPlant().y)));
	return xPosTrue && yPosTrue;
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
	case WM_KEYDOWN :	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			_game->GetPlayerInTurn()->SetPassed();
			break;
		}
		default:
			break;
		}
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
	wc.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
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