#ifndef GAME_H
#define GAME_H

#include "Draw.h"
#include "GameBoard.h"
//#include "Map.h" TODO remove
#include "Player.h"

#include <algorithm>
#include <stdlib.h>
#include <time.h> 
#include <vector>

class Game
{
public:
	Game(HWND);
	~Game() {};

private:
	Draw _draw = Draw();
	//Map _map = Map();
	std::vector<Player> _players;
	GameBoard _gameBoard = GameBoard();

	bool _gameOver = false;

public:
	void Run();
	void DrawScreen();

	bool GetGameOver();
	void InitGame();
	//void SetPlayerKeyDown(Game::PlayerControl, bool);

private:
	Draw* GetDraw();
};

#endif // !GAME_H