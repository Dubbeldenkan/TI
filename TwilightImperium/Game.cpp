#include "Game.h"

Player* Game::_currentPlayer = NULL;

Game::Game()
{
	InitGame();
}

void Game::Run()
{
	//TODO �ndra till ett l�mpligt villkor
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
				StrategyPhase();
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
			else
			{
				StatusPhase();
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
	_players.push_back(Player(Race::BaronyOfLetnev, GraphicsNS::Graphics::RED, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::EmiratesOfHacan, GraphicsNS::Graphics::BLUE, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::FederationOfSol, GraphicsNS::Graphics::PURPLE, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::L1Z1XMindnet, GraphicsNS::Graphics::YELLOW, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::MentakCoalition, GraphicsNS::Graphics::GREEN, _gameBoard.GetMapMap(), _players.size()));
	_players.push_back(Player(Race::NaaluCollective, GraphicsNS::Graphics::WHITE, _gameBoard.GetMapMap(), _players.size()));
	
	_currentPlayer = &_players[rand() % _players.size()];

	_gamePhase = STRATEGY_PHASE;
}

void Game::InitStrategyPhase()
{
	_initPhase = false;
}

void Game::StrategyPhase()
{
	_initPhase = true;
	_gamePhase = ACTION_PHASE;
}

void Game::InitActionPhase()
{
	_initPhase = false;
	for (int playerCount = 0; playerCount < static_cast<int>(_players.size()); playerCount++)
	{
		_players[playerCount].PrepareForGameRound();
	}
	//TODO �ndra detta till r�tt strategy kort
	_currentPlayer = &_players[0];
}

//TODO �ndra till strategyCard ist�llet f�r ordningen. 
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
				_gamePhase = STATUS_PHASE; //�r detta r�tt s�tt att g�ra det p�?
				_initPhase = true;
				nextPlayerIsSet = true;
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

void Game::StatusPhase()
{
	_gamePhase = STRATEGY_PHASE;
	_initPhase = true;
}

void Game::MouseClicked(TupleInt mouseClickedPos)
{
	std::vector<GameBoardObject*> clickedObjects = GameBoard::GetGameBoardObjectByPosition(mouseClickedPos);
	for (int vectorCount = 0; vectorCount < static_cast<int>(clickedObjects.size()); vectorCount++)
	{
		GameBoardObject* object = clickedObjects[vectorCount];
		_currentPlayer->Action(object);
	}
}

void Game::MouseMoved(TupleInt mousePos)
{
	//TODO ska denna logik flyttas in i Player?
	if (_currentPlayer->GetActionState() == Player::TACTICAL_ACTION && 
		_currentPlayer->GetSubActionState() == Player::ACTIVATE_A_SYSTEM)
	{
		_currentPlayer->SetCommandCounterPos(mousePos);
	}
}