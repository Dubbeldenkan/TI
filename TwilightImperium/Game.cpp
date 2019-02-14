#include "Game.h"

Game::Game(HWND hWnd)
{
	//init rand
	srand((unsigned int)time(NULL));

	_draw = Draw(&hWnd);
	//_map.InitMap(_draw.GetGraphics());
	//_players.push_back(Player(true));
	//_localPlayer = &_players[0]; //Get a pointer to the first player

	InitGame();
}

int Game::GetSleepTimeInMs()
{
	return _sleepTimeInMs;
}

void Game::Run()
{
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
	//Draw::DrawInput dI;
	//dI.map = &_map;
	//dI.player = _localPlayer;
	//_draw.DrawScreen(&dI);
}

Draw* Game::GetDraw()
{
	return &_draw;
}

bool Game::GetGameOver()
{
	return _gameOver;
}

void Game::InitGame()
{
	//TODO
}