#include "Game.h"

const int Game::NumberOfCitiesToStep2[] = { 10, 7, 7, 7, 6 };
const int Game::NumberOfCitiesToEndGame[] = { 21, 17, 17, 15, 14 };

Game::Game(HWND hWnd)
{
	//init rand
	srand(time(NULL));
		
	std::vector<int> usedRegions;
	InitPlayers();

	usedRegions.push_back(0);
	usedRegions.push_back(1);
	usedRegions.push_back(2);
	if (_numberOfPlayers > 3)
	{
		usedRegions.push_back(3);
	}
	if (_numberOfPlayers > 4)
	{
		usedRegions.push_back(4);
	}
	for (int index = 0; index < _numberOfPlayers; index++)
	{
		usedRegions.push_back(index);
	}
	_board = new Board(usedRegions, "Map/USAPowerGrid.png");
	_draw = Draw(&hWnd, _board);
	_ppm = PowerPlantMarket();
	_rm = new ResourceMarket(_numberOfPlayers, ResourceMarket::USA);
}

void Game::InitPlayers()
{
	std::ifstream file("Settings");

	if (file)
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string line;
		file.close();

		std::getline(buffer, line);
		_numberOfPlayers = std::min(std::stoi(line), MAX_PLAYERS);
		std::getline(buffer, line);
		int numberOfHumanPlayers = std::min(std::stoi(line), _numberOfPlayers);

		int usedColorsArray[MAX_PLAYERS];
		for (int index = 0; index < MAX_PLAYERS; index++)
		{
			usedColorsArray[index] = index;
		}
		int playerIndex = 0;
		while (std::getline(buffer, line))
		{
			bool isAI = true;
			if (numberOfHumanPlayers > playerIndex)
			{
				isAI = false;
			}
			std::string name = line;
			std::getline(buffer, line);
			std::string colorName = line;
			Player::Color playerColor = GetPlayerColorFromString(colorName);
			_pv.push_back(Player(name, playerColor, !isAI, playerIndex));
			for (int index = 0; index < MAX_PLAYERS; index++)
			{
				if ((int)playerColor == usedColorsArray[index])
				{
					usedColorsArray[index] = -1;
					break;
				}
			}
			playerIndex++;
		}
		for (playerIndex; playerIndex < _numberOfPlayers; playerIndex++)
		{
			bool isAI = true;
			if (numberOfHumanPlayers > playerIndex)
			{
				isAI = false;
			}
			std::string playerName = "player";
			playerName += std::to_string(playerIndex + 1);
			int colorIndex = 0;
			while (usedColorsArray[colorIndex] == -1)
			{
				colorIndex++;
			}
			_pv.push_back(Player((char*)playerName.c_str(), 
				(Player::Color) usedColorsArray[colorIndex], !isAI, playerIndex));
			usedColorsArray[colorIndex] = -1;
		}
	}
}

Player::Color Game::GetPlayerColorFromString(std::string colorName)
{
	Player::Color result = Player::black;
	if (colorName.compare("R�d") == 0)
	{
		result = Player::red;
	}
	else if (colorName.compare("Bl�") == 0)
	{
		result = Player::blue;
	}
	else if (colorName.compare("Gr�n") == 0)
	{
		result = Player::green;
	}
	else if (colorName.compare("Lila") == 0)
	{
		result = Player::purple;
	}
	else if (colorName.compare("Gul") == 0)
	{
		result = Player::yellow;
	}
	else if (colorName.compare("Svart") == 0)
	{
		result = Player::black;
	}
	return result;
}

int Game::GetCurrentPhase()
{
	return _gamePhase;
}

int Game::GetNumberOfPlayers()
{
	return _numberOfPlayers;
}

int Game::GetSelectedPowerPlant()
{
	return _phase2Struct.selectedPowerPlant - 1;
}

int Game::GetLastBidForSelectedPowerPlant()
{
	return _phase2Struct.bidForSelectedPowerPlant;
}

Game::GameSubPhase Game::GetCurrentSubPhase()
{
	return _gameSubPhase;
}

int Game::GetNextBid()
{
	return _phase2Struct.nextBid;
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
	return _phase2Struct.bidForSelectedPowerPlant;
}

ResourceMarket* Game::GetResourceMarket()
{
	return _rm;
}

Board* Game::GetBoard()
{
	return _board;
}

Player* Game::GetLastBiddingPlayer()
{
	return _phase2Struct.lastBiddingPlayer;
}

int Game::GetGameTurn()
{
	return _gameTurn;
}

void Game::IncreaseNextBid(int change)
{
	_phase2Struct.buttonPressed = true;
	_phase2Struct.nextBid = std::max(_phase2Struct.nextBid + change,
		_phase2Struct.bidForSelectedPowerPlant + 1);
}

void Game::SetNextPlayerInTurn(std::vector<Player*> *tempVector, int direction)
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
	if (currentPlayerPos == (tempVector->size() - 1) && direction == 1)
	{
		_playerInTurn = (*tempVector)[0];
	}
	else if (currentPlayerPos == 0 && direction == -1)
	{
		_playerInTurn = (*tempVector)[tempVector->size() - 1];
	}
	else
	{
		_playerInTurn = (*tempVector)[currentPlayerPos + direction];
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

std::vector<Player*> Game::GetPlayerVector()
{
	std::vector<Player*> playerVector;
	for (int index = 0; index < _numberOfPlayers; index++)
	{
		playerVector.push_back(&_pv[index]);
	}
	return playerVector;
}

void Game::RemovePlayerFromTempVector(std::vector<Player*> *tempVector, int direction)
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
	SetNextPlayerInTurn(tempVector, direction);
	tempVector->erase(tempVector->begin() + currentPlayerPos);
}

int Game::GetNewCityCost(char* cityName)
{
	City* tempCity = _board->GetCityFromName(cityName);
	return  tempCity->GetCostForFirstFreePos(_gameStep);
}

void Game::PrintDataToLog(int tempGameTurn)
{
	if (_gameTurn != tempGameTurn)
	{
		for (int index = 0; index < _numberOfPlayers; index++)
		{
			_pv[index].PrintPlayerData(_gameTurn);
		}
		_ppm.PrintPowerPlantData(_gameTurn);
		_rm->PrintResourceMarketData(_gameTurn);
	}
}

void Game::CheckAndUpdateForStep2()
{
	if (_gameStep == 1)
	{
		for (int index = 0; index < _numberOfPlayers; index++)
		{
			if (_pv[index].GetNumberOfCitiesInNetwork() >= NumberOfCitiesToStep2[_numberOfPlayers - 2])
			{
				_gameStep = 2;
			}
		}
	}
}

void Game::CheckAndUpdateForStep3()
{
	if (_gameStep == 1 || _gameStep == 2)
	{
		if (_ppm.GetStep3())
		{
			_gameStep = 3;
			_ppm.UpdateToStep3();
		}
	}
}

void Game::Run()
{
	int tempGameTurn = _gameTurn;
	switch (_gamePhase)
	{
	case 1:
		Phase1();
		break;
	case 2:
		Phase2();
		break;
	case 3:
		Phase3();
		break;
	case 4:
		Phase4();
		break;
	case 5:
		Phase5();
		break;
	case 6:
		EndGame();
		break;
	default:
		break;
	}
	PrintDataToLog(tempGameTurn);
}

void Game::DrawBoard()
{
	std::vector<Player*> tempVector;
	for (int i = 0; i < _numberOfPlayers; i++)
	{
		tempVector.push_back(&_pv[i]);
	}
	Draw::DrawInput dI;
	dI.board = _board;
	dI.playerVector = tempVector;
	dI.playerInTurn = _playerInTurn;
	dI.powerPlantMarket = &_ppm;
	dI.resourceMarket = _rm;
	dI.gamePhase = _gamePhase;
	dI.gameTurn = _gameTurn;
	dI.gameStep = _gameStep;

	dI.selectedPowerPlant = _phase2Struct.selectedPowerPlant - 1;
	dI.currentPowerPlantBiddingPrice = _phase2Struct.bidForSelectedPowerPlant;
	dI.lastBiddingPlayer = _phase2Struct.lastBiddingPlayer;
	dI.nextBid = _phase2Struct.nextBid;
	dI.placePowerPlant = _gameSubPhase == placePowerPlant;
	dI.regionsInPlay = _board->GetRegionsInPlay();

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
		_pv.clear();
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
				if (bestValue == 0)
				{
					while (!tempPv.empty())
					{
						_pv.push_back(tempPv[0]);
						tempPv.erase(tempPv.begin());
					}
					break;
				}
				else
				{
					_pv.push_back(tempPv[bestValuePos]);
					tempPv.erase(tempPv.begin() + bestValuePos);
				}
			}
			else
			{
				_pv.push_back(tempPv[playersWithBestValue[0]]);
				tempPv.erase(tempPv.begin() + playersWithBestValue[0]);
			}
		}
	}
	_playerInTurn = &_pv[0];
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
			_tempPlayerVector[i]->ResetPassed();
		}
		_gameSubPhase = choosePowerPlant;
		_playerInTurn = _tempPlayerVector[0];
		_phase2Struct.allHasPassed = true;
		break;
	}
	case choosePowerPlant:
	{
		//player passes
		if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_tempPlayerVector, 1);
			if (_tempPlayerVector.size() == 0)
			{
				_gameSubPhase = nextPhase;
			}
			DrawBoard();
		}
		else if(_playerInTurn->GetSelectedPowerPlant() > 0)
		{
			_phase2Struct.allHasPassed = false;
			_phase2Struct.selectedPowerPlant = _playerInTurn->GetSelectedPowerPlant();
			_phase2Struct.bidForSelectedPowerPlant = 
				_ppm.GetPowerPlantCurrentDeck(_phase2Struct.selectedPowerPlant - 1)->GetPowerPlantNumber();
			_playerInTurn->ResetSelectedPowerPlant();
			_phase2Struct.lastBiddingPlayer = _playerInTurn;
			_phase2Struct.nextBid = _phase2Struct.bidForSelectedPowerPlant + 1;
			_gameSubPhase = bid;
			_phase2Struct.bidPlayerVector = _tempPlayerVector;
			SetNextPlayerInTurn(&_tempPlayerVector, 1);
			DrawBoard();
		}
		break;
	}
	case bid:
	{
		if (_phase2Struct.bidPlayerVector.size() == 1)
		{
			_gameSubPhase = placePowerPlant;
			DrawBoard();
		}
		else if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_phase2Struct.bidPlayerVector, 1);
			_phase2Struct.nextBid = _phase2Struct.bidForSelectedPowerPlant + 1;
			DrawBoard();
		}
		else if (_phase2Struct.buttonPressed)
		{
			_phase2Struct.buttonPressed = false;
			DrawBoard();
		}
		else if (_playerInTurn->NewBid())
		{
			_playerInTurn->ResetBid();
			_phase2Struct.bidForSelectedPowerPlant = _phase2Struct.nextBid;
			_phase2Struct.lastBiddingPlayer = _playerInTurn;
			_phase2Struct.nextBid = _phase2Struct.bidForSelectedPowerPlant + 1;
			SetNextPlayerInTurn(&_phase2Struct.bidPlayerVector, 1);
			DrawBoard();
		}
		break;
	}
	case placePowerPlant:
	{
		if (_playerInTurn->GetNewPowerPlantPos() > -1)
		{
			_playerInTurn->AddPowerPlant(_ppm.GetPowerPlantCurrentDeck(_phase2Struct.selectedPowerPlant - 1),
				_phase2Struct.bidForSelectedPowerPlant);
			_ppm.RemovePowerPlant(_phase2Struct.selectedPowerPlant - 1);
			RemovePlayerFromTempVector(&_tempPlayerVector, 1);
			_phase2Struct.selectedPowerPlant = 0;
			DrawBoard();
			if (_tempPlayerVector.size() > 0)
			{
				_gameSubPhase = choosePowerPlant;
			}
			else
			{
				_gameSubPhase = nextPhase;
			}
			DrawBoard();
		}
		break;
	}
	case nextPhase:
	{
		if (_phase2Struct.allHasPassed && !_ppm.PowerPlantDeckIsEmpty())
		{
			_ppm.RemoveLowestPowerPlant();
		}
		_gamePhase++;
		_gameSubPhase = initPhase;
		break;
	}
	default:
		break;
	}
}

void Game::Phase3()
{
	switch (_gameSubPhase)
	{
	case initPhase:
	{
		_gameSubPhase = buyResources;
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_tempPlayerVector.push_back(&_pv[i]);
			_tempPlayerVector[i]->ResetPassed();
		}
		_playerInTurn = _tempPlayerVector[_tempPlayerVector.size() - 1];
		DrawBoard();
		break;
	}
	case buyResources:
	{
		if(_playerInTurn->GetTradeOk())
		{
			int resourceAmount = _playerInTurn->GetAmountOfResource();
			ResourceMarket::Resource resource = _playerInTurn->GetResourceType();
			_rm->TransferResources(resourceAmount, resource);
			_playerInTurn->TransferResources();
			DrawBoard();
		}
		else if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_tempPlayerVector, -1);
			if (_tempPlayerVector.size() < 1)
			{
				_gameSubPhase = nextPhase;
			}
			DrawBoard();
		}
		break;
	}
	case nextPhase:
	{
		_gamePhase++;
		_gameSubPhase = initPhase;
		break;
	}
	default:
		break;
	}
}

void Game::Phase4()
{
	switch (_gameSubPhase)
	{
	case initPhase:
		_gameSubPhase = buildCities;
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_tempPlayerVector.push_back(&_pv[i]);
		}
		_playerInTurn = _tempPlayerVector[_tempPlayerVector.size() - 1];
		DrawBoard();
		break;
	case buildCities:
	{
		if (_playerInTurn->GetClickedOnNewCity())
		{
			int cityCost = GetNewCityCost(_playerInTurn->GetNewCityName());
			Board::GetRoadCostOutput result = _board->GetRoadCost(_playerInTurn->GetCityVector(), _playerInTurn->GetNewCityName());
			int roadCost = result.cost;
			if((cityCost != 0) && (_playerInTurn->CanAffordCost(cityCost + roadCost)))
			{
				City* city = _board->GetCityFromName(_playerInTurn->GetNewCityName());
				city->SetFirstFreePos((int) _playerInTurn->GetColor());
				_playerInTurn->BuyCity(cityCost + roadCost, city, result.cityList);
				DrawBoard();
			}
			else
			{
				_playerInTurn->ResetClickedOnNewCity();
			}
		}
		else if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_tempPlayerVector, -1);
			if (_tempPlayerVector.size() < 1)
			{
				_gameSubPhase = nextPhase;
			}
			DrawBoard();
		}
		break;
	}
	case nextPhase:
	{
		_gamePhase++;
		_gameSubPhase = initPhase;
		break;
	}
		break;
	default:
		break;

	}
}

void Game::Phase5()
{
	switch (_gameSubPhase)
	{
	case initPhase:
	{
		_gameSubPhase = choosePowerPlantsToProducePower;
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_pv[i].ActiveThePowerPlants();
			_tempPlayerVector.push_back(&_pv[i]);
			_tempPlayerVector[i]->ResetPassed();
		}
		_playerInTurn = _tempPlayerVector[0];
		DrawBoard();
		break;
	}
	case choosePowerPlantsToProducePower:
	{
		if (_playerInTurn->GetPassed())
		{
			RemovePlayerFromTempVector(&_tempPlayerVector, 1);
			if (_tempPlayerVector.size() < 1)
			{
				_gameSubPhase = getPayed;
			}
			DrawBoard();
		}
		else if (_playerInTurn->GetPowerPlantClicked())
		{
			_playerInTurn->ResetPowerPlantClicked();
			DrawBoard();
		}
		break;
	}
	case getPayed:
	{
		for (int i = 0; i < _numberOfPlayers; i++)
		{
			_pv[i].GetPayed();
		}
		CheckAndUpdateForStep2();
		_ppm.RemoveHighestPowerPlant();
		CheckAndUpdateForStep3();
		CheckIfGameHasEnded();
		_rm->ReSupplyResourceMarket(_gameStep);
		_gameSubPhase = nextPhase;
		break;
	}
	case nextPhase:
	{
		_gameSubPhase = initPhase;
		_gamePhase = 1;
		_gameTurn++;
		DrawBoard();
		break;
	}
	}
}

void Game::CheckIfGameHasEnded()
{
	for (int index = 0; index < _numberOfPlayers; index++)
	{
		if (_pv[index].GetNumberOfCitiesInNetwork() >= NumberOfCitiesToEndGame[_numberOfPlayers - 2])
		{
			_gamePhase = 6;
			_gameHasAWinner = true;
			break;
		}
	}
	if (_ppm.PowerPlantDeckIsEmpty())
	{
		_gamePhase = 7;
		_gameHasAWinner = false;
	}
}

void Game::EndGame()
{
	std::vector<Player> tempPv;
	tempPv = _pv;
	_pv.clear();
	for (int order = 0; order < _numberOfPlayers; order++)
	{
		int playersLeft = tempPv.size();
		int bestValue = 0;
		std::vector<int> playersWithBestValue;
		for (int index = 0; index < playersLeft; index++)
		{
			if (tempPv[index].GetNumberOfSuppliedCities() > bestValue)
			{
				bestValue = tempPv[index].GetNumberOfSuppliedCities();
				playersWithBestValue.clear();
				playersWithBestValue.push_back(index);
			}
			else if (tempPv[index].GetNumberOfSuppliedCities() == bestValue)
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
				if (tempPv[playersWithBestValue[index]].GetAmountOfElektro() > bestValue)
				{
					bestValue = tempPv[playersWithBestValue[index]].GetAmountOfElektro();
					bestValuePos = playersWithBestValue[index];
				}
			}
			if (bestValue == 0)
			{
				while (!tempPv.empty())
				{
					_pv.push_back(tempPv[0]);
					tempPv.erase(tempPv.begin());
				}
				break;
			}
			else
			{
				_pv.push_back(tempPv[bestValuePos]);
				tempPv.erase(tempPv.begin() + bestValuePos);
			}
		}
		else
		{
			_pv.push_back(tempPv[playersWithBestValue[0]]);
			tempPv.erase(tempPv.begin() + playersWithBestValue[0]);
		}
	}
	_playerInTurn = &_pv[0];
	DrawBoard();
	_gamePhase++;
}

void Game::ResetGame()
{
	_gamePhase = 1;
	_gameStep = 1;
	_gameSubPhase = initPhase;
	_gameTurn = 1;

	_board->ResetBoard();
	_rm->ResetResourceMarket();
	_ppm.ResetPowerPlantMarket();
	for (int index = 0; index < _numberOfPlayers; index++)
	{
		_pv[index].ResetPlayer();
	}
}

bool Game::GetGameHasAWinner()
{
	return _gameHasAWinner;
}