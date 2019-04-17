#include "Game.h"

Game::Game()
{
	InitGame();
}

void Game::Run()
{
	DrawScreen();
	//TODO ändra till ett lämpligt villkor
	/*if (true)
	{
		_localPlayer->MoveScreen();
	}
	else
	{
		//game over
		_gameOver = true;
	}*/
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
}