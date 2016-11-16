#include "Game.h"

Game::Game(int numberOfPlayers, HWND hWnd)
{
	//init rand
	srand(time(NULL));
	
	_numberOfPlayers = numberOfPlayers;
	_board = Board(true, true, true, false, false, false, "Map/USAPowerGrid.png");
	_draw = Draw(&hWnd, &_board);
	_ppm = PowerPlantMarket();
	_rm = new ResourceMarket(numberOfPlayers, ResourceMarket::USA);
	InitPlayers(numberOfPlayers);
}

void Game::InitPlayers(int numberOfPlayers)
{
	_pv.push_back(Player("Dennis", Player::red));
	_pv.push_back(Player("Alida", Player::blue));
	_pv.push_back(Player("Edwin", Player::green));
	_playerInTurn = &_pv[0];
}

int Game::GetCurrentPhase()
{
	return _gamePhase;
}

Game::GameSubPhase Game::GetCurrentSubPhase()
{
	return _gameSubPhase;
}

int Game::GetCurrentStep()
{
	return _gameStep;
}

Draw* Game::GetDraw()
{
	return &_draw;
}

Player* Game::GetPlayerInTurn()
{
	return _playerInTurn;
}

PowerPlantMarket* Game::GetPowerPlantMarket()
{
	return &_ppm;
}

int Game::GetBidForSelectedPowerPlant()
{
	return _phase2Struct._bidForSelectedPowerPlant;
}

void Game::IncreaseNextBid(int change)
{
	_phase2Struct._buttonPressed = true;
	_phase2Struct._nextBid = std::max(_phase2Struct._nextBid + change,
		_phase2Struct._bidForSelectedPowerPlant + 1);
}

void Game::SetNextPlayerInTurn(std::vector<Player*> *tempVector)
{
	int currentPlayerPos;
	for (int index = 0; index < tempVector->size(); index++)
	{
		if ((*tempVector)[index] == _playerInTurn)
		{
			currentPlayerPos = index;
			break;
		}
	}
	if (currentPlayerPos == (tempVector->size() - 1))
	{
		_playerInTurn = (*tempVector)[0];
	}
	else
	{
		_playerInTurn = (*tempVector)[currentPlayerPos + 1];
	}
}

int Game::GetPlayerInTurnPosition()
{
	int playerInTurnPosition;
	for (int index = 0; index < _numberOfPlayers; index++)
	{
		if (_playerInTurn == &_pv[index])
		{
			playerInTurnPosition = index;
			break;
		}
	}
	return playerInTurnPosition;
}

void Game::RemovePlayerFromTempVector(std::vector<Player*> *tempVector)
{
	_playerInTurn->ResetPassed();
	int currentPlayerPos;
	for (int index = 0; index < tempVector->size(); index++)
	{
		if ((*tempVector)[index] == _playerInTurn)
		{
			currentPlayerPos = index;
			break;
		}
	}
	SetNextPlayerInTurn(tempVector);
	tempVector->erase(tempVector->begin() + currentPlayerPos);
}

void Game::Run()
{
	switch (_gamePhase)
	{
	case 1:
		Phase1();
		break;
	case 2:
		Phase2();
		break;
	default:
		break;
	}
}

void Game::DrawBoard()
{
	std::vector<Player*> tempVector;
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		tempVector.push_back(&_pv[i]);
	}
	Draw::DrawInput dI;
	dI._board = &_board;
	dI._playerVector = tempVector;
	dI._playerInTurn = _playerInTurn;
	dI._powerPlantMarket = &_ppm;
	dI._resourceMarket = _rm;
	dI._gamePhase = _gamePhase;

	dI._selectedPowerPlant = _phase2Struct._selectedPowerPlant - 1;
	dI._currentPowerPlantBiddingPrice = _phase2Struct._bidForSelectedPowerPlant;
	dI._lastBiddingPlayer = _phase2Struct._lastBiddingPlayer;
	dI._nextBid = _phase2Struct._nextBid;
	dI._placePowerPlant = _gameSubPhase == placePowerPlant;

	_draw.DrawWholeBoard(&dI);
}

void Game::Phase1()
{
	std::vector<Player> tempPv;
	if (_gameTurn == 1)
	{
		int startIndex = rand() % _numberOfPlayers;
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			int index = (startIndex + i) % _numberOfPlayers;
			tempPv.push_back(_pv[index]);
		}
		_pv = tempPv;
	}
	else
	{
		tempPv = _pv;
		for (int order = 0; order < _numberOfPlayers; order++)
		{
			int playersLeft = tempPv.size();
			int bestValue = 0;
			std::vector<int> playersWithBestValue;
			for (int index = 0; index < playersLeft; index++)
			{
				if (tempPv[index].GetNumberOfCitiesInNetwork() > bestValue)
				{
					bestValue = tempPv[index].GetNumberOfCitiesInNetwork();
					playersWithBestValue.clear();
					playersWithBestValue.push_back(index);
				}
				else if (tempPv[index].GetNumberOfCitiesInNetwork() == bestValue)
				{
					playersWithBestValue.push_back(index);
				}
			}
			if (playersWithBestValue.size() > 1)
			{
				int playersLeft = playersWithBestValue.size();
				int bestValue = 0;
				int bestValuePos;
				for (int index = 0; index < playersLeft; index++)
				{
					if (tempPv[playersWithBestValue[index]].GetNumberFromHighestPowerPlant() > bestValue)
					{
						bestValue = tempPv[playersWithBestValue[index]].GetNumberFromHighestPowerPlant();
						bestValuePos = playersWithBestValue[index];
					}
				}
				_pv.push_back(tempPv[bestValuePos]);
				tempPv.erase(tempPv.begin() + bestValuePos);
			}
		}
	}
	_gamePhase++;
	DrawBoard();
}

void Game::Phase2()
{
	switch (_gameSubPhase)
	{
	case initPhase:
	{
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_tempPlayerVector.push_back(&_pv[i]);
		}
		_gameSubPhase = choosePowerPlant;
		_playerInTurn = _tempPlayerVector[0];
		break;
	}
	case choosePowerPlant:
	{
		//player passes
		if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_tempPlayerVector);
			if (_tempPlayerVector.size() == 0)
			{
				_gameSubPhase = Game::nextPhase;
			}
			DrawBoard();
		}
		else if(_playerInTurn->GetSelectedPowerPlant() > 0)
		{
			_phase2Struct._selectedPowerPlant = _playerInTurn->GetSelectedPowerPlant();
			_phase2Struct._bidForSelectedPowerPlant = 
				_ppm.GetPowerPlantCurrentDeck(_phase2Struct._selectedPowerPlant - 1)->GetPowerPlantNumber();
			_playerInTurn->ResetSelectedPowerPlant();
			_phase2Struct._lastBiddingPlayer = _playerInTurn;
			_phase2Struct._nextBid = _phase2Struct._bidForSelectedPowerPlant + 1;
			_gameSubPhase = bid;
			_phase2Struct._bidPlayerVector = _tempPlayerVector;
			SetNextPlayerInTurn(&_tempPlayerVector);
			DrawBoard();
		}
		break;
	}
	case bid:
	{
		if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_phase2Struct._bidPlayerVector);
			_phase2Struct._nextBid = _phase2Struct._bidForSelectedPowerPlant + 1;
			DrawBoard();
		}
		else if (_phase2Struct._buttonPressed)
		{
			_phase2Struct._buttonPressed = false;
			DrawBoard();
		}
		else if (_playerInTurn->NewBid())
		{
			_playerInTurn->ResetBid();
			_phase2Struct._bidForSelectedPowerPlant = _phase2Struct._nextBid;
			_phase2Struct._lastBiddingPlayer = _playerInTurn;
			_phase2Struct._nextBid = _phase2Struct._bidForSelectedPowerPlant + 1;
			SetNextPlayerInTurn(&_phase2Struct._bidPlayerVector);
			DrawBoard();
		}
		else if (_phase2Struct._bidPlayerVector.size() == 1)
		{
			_gameSubPhase = placePowerPlant;
			DrawBoard();
		}
		break;
	}
	case placePowerPlant:
	{
		if (_playerInTurn->GetNewPowerPlantPos() > -1)
		{
			_playerInTurn->AddPowerPlant(_ppm.GetPowerPlantCurrentDeck(_phase2Struct._selectedPowerPlant - 1),
				_phase2Struct._bidForSelectedPowerPlant);
			_ppm.RemovePowerPlant(_phase2Struct._selectedPowerPlant - 1);
			RemovePlayerFromTempVector(&_tempPlayerVector);
			_phase2Struct._selectedPowerPlant = 0;
			_gameSubPhase = choosePowerPlant;
			DrawBoard();
		}
		break;
	}
	default:
		break;
	}
}

void Game::Phase3()
{

}

void Game::Phase4()
{

}

void Game::Phase5()
{

}