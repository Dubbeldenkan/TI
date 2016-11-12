#include "Game.h"

Game::Game(int numberOfPlayers, HWND hWnd)
{
	//init rand
	srand(time(NULL));
	
	_numberOfPlayers = numberOfPlayers;
	_board = Board(true, true, true, false, false, false, "USAPowerGrid.png");
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
	_draw.DrawWholeBoard(&_board, tempVector, _playerInTurn, &_ppm, _selectedPowerPlant - 1, _rm);
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
	DrawBoard();
	_gamePhase++;
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
		if (_playerInTurn->GetSelectedPowerPlant() == -1)
		{
			_tempPlayerVector.erase(_tempPlayerVector.begin());
			if (_tempPlayerVector.size() == 0)
			{
				_gameSubPhase = Game::nextPhase;
			}
			DrawBoard();
		}
		else if(_playerInTurn->GetSelectedPowerPlant() > 0)
		{
			_selectedPowerPlant = _playerInTurn->GetSelectedPowerPlant();
			_playerInTurn->ResetSelectedPowerPlant();
			_gameSubPhase = bid;
			//TODO
			//SetNextPlayerInTurn();
			DrawBoard();
		}
		break;
	}
	case bid:
	{

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