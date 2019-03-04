#include "Game.h"

Game::Game()
{
	//_players.push_back(Player(true));
	//_localPlayer = &_players[0]; //Get a pointer to the first player

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
	//TODO
}