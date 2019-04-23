#include "Game.h"

Player* Game::_currentPlayer = NULL;

Game::Game()
{
	InitGame();
}

void Game::Run()
{
	//TODO ändra till ett lämpligt villkor
	if (true)
	{
		switch (_gamePhase)
		{
		case Game::STRATEGY_PHASE:
			if (_initPhase)
			{
				InitStrategyPhase();
			}
			else
			{
				_initPhase = true;
				_gamePhase = ACTION_PHASE;
			}
			break;
		case Game::ACTION_PHASE:
			if (_initPhase)
			{
				InitActionPhase();
			}
			else
			{
				ActionPhase();
			}
			break;
		case Game::STATUS_PHASE:
			if (_initPhase)
			{
				InitStatusPhase();
			}
			break;
		default:
			break;
		}
		_gameBoard.Run(_currentPlayer);
		DrawScreen();
	}
	else
	{
		_gameOver = true;
	}
}

void Game::DrawScreen()
{
	_gameBoard.Draw();
}

bool Game::GetGameOver()
{
	return _gameOver;
}

void Game::InitGame()
{
	_players.push_back(Player(Race::BaronyOfLetnev, Player::Red, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::EmiratesOfHacan, Player::Blue, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::FederationOfSol, Player::Purple, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::L1Z1XMindnet, Player::Yellow, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::MentakCoalition, Player::Green, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::NaaluCollective, Player::White, _gameBoard.GetMapMap(), _players.size()));
	
	_currentPlayer = &_players[rand() % _players.size()];

	_gamePhase = STRATEGY_PHASE;
}

void Game::InitStrategyPhase()
{
	_initPhase = false;
}

void Game::InitActionPhase()
{
	_initPhase = false;
	for (int playerCount = 0; playerCount < static_cast<int>(_players.size()); playerCount++)
	{
		_players[playerCount].PrepareForGameRound();
	}
	//TODO ändra detta till rätt strategy kort
	_currentPlayer = &_players[0];
}

//TODO ändra till strategyCard istället för ordningen. 
void Game::ActionPhase()
{
	if (_currentPlayer->TurnIsFinished())
	{
		bool nextPlayerIsSet = false;
		int startPosInPlayerOrder = _currentPlayer->GetPosInPlayerOrder();
		int posInPlayerOrder = startPosInPlayerOrder;
		while (!nextPlayerIsSet)
		{
			posInPlayerOrder++;
			if (posInPlayerOrder == startPosInPlayerOrder)
			{
				_gamePhase = STATUS_PHASE; //Är detta rätt sätt att göra det på?
				_initPhase = true;
			}
			else
			{
				posInPlayerOrder = posInPlayerOrder % static_cast<int>(_players.size());
				if (!_players[posInPlayerOrder].GetPlayerHasPassed())
				{
					_currentPlayer = &_players[posInPlayerOrder];
					nextPlayerIsSet = true;
				}
			}
		}
	}
}

void Game::InitStatusPhase()
{
	_initPhase = false;
}

void Game::ClickAction(std::vector<GameBoardObject*> objectVector)
{
	for (int vectorCount = 0; vectorCount < static_cast<int>(objectVector.size()); vectorCount++)
	{
		GameBoardObject* object = objectVector[vectorCount];
		object->Action(_currentPlayer);
	}
}