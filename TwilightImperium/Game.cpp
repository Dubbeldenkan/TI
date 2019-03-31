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
	for (int playerCount = 0; playerCount < _numberOfPlayers; playerCount++)
	{
		_players.push_back(Player(Race::BaronyOfLetnev, _gameBoard.GetMapMap()));
	}
}