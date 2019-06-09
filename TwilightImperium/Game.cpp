#include "Game.h"

Player* Game::_currentPlayer = NULL;
bool Game::_initNewGame = false;
bool Game::_saveGame = false;
bool Game::_loadGame = false;

Game::Game()
{
	InitGame();
}

void Game::Run()
{
	if (_saveGame)
	{
		SaveGame();
	}

	if (_initNewGame)
	{
		//TODO starta om ett spel här..
	}
	else if (_loadGame)
	{
		//TODO ladda ett spel här
	}
	//TODO ändra till ett lämpligt villkor
	else if (true)
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

void Game::SetInitNewGame()
{
	_initNewGame = true;
}

void Game::SetSaveGame()
{
	_saveGame = true;
}

void Game::SetLoadGame()
{
	_loadGame = true;
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

void Game::SaveGame()
{
	_saveGame = false;
	TIParserNS::ListNode gameToSave = TIParserNS::ListNode("Game");
	CreateSaveNode(&gameToSave);
	SaveToFile(&gameToSave);
}

void Game::CreateSaveNode(TIParserNS::ListNode* gameNode)
{
	// Players
	TIParserNS::ListNode* playersNode = new TIParserNS::ListNode("Players");
	gameNode->SetChild(playersNode);
	TIParserNS::ListNode* currentNode = new TIParserNS::ListNode(""); //TODO är detta en poteentiell minnesläcka?
	TIParserNS::ListNode* oldNode = NULL;
	for (int playerCount = 0; playerCount < static_cast<int>(_players.size()); playerCount++)
	{
		_players[playerCount].Save(&currentNode);
		if (oldNode == NULL) //TODO kan man göra detta på ett snyggare sätt?
		{
			playersNode->SetChild(currentNode);
		}
		else
		{
			oldNode->SetNext(currentNode);
		}
		oldNode = currentNode;
	}

	//Gameboard
	TIParserNS::ListNode* gameBoardNode = _gameBoard.Save();
	playersNode->SetNext(gameBoardNode);
}

void Game::SaveToFile(TIParserNS::ListNode* gameToSave)
{
	time_t rawtime = time(NULL);
	struct tm timeInfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeInfo, &rawtime);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &timeInfo);

	std::string fileName = "savedGame_";
	fileName = fileName + buffer;

	TIParserNS::TIParser::WriteToFile(gameToSave, fileName);
}