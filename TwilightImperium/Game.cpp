#include "Game.h"

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
			StrategyPhase();
			break;
		case Game::ACTION_PHASE:
			ActionPhase();
			break;
		case Game::STATUS_PHASE:
			StatusPhase();
			break;
		default:
			break;
		}
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

	_gamePhase = STRATEGY_PHASE;
}

void Game::StrategyPhase()
{
	_gamePhase = ACTION_PHASE;
	for (int playerCount = 0; playerCount < static_cast<int>(_players.size()); playerCount++)
	{
		_players[playerCount].PrepareForGameRound();
	}
}

void Game::ActionPhase()
{

}

void Game::StatusPhase()
{

}