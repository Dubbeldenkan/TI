#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "Player.h"
#include "UnitStack.h"

#include <algorithm>
#include <stdlib.h>
#include <time.h> 
#include <vector>

class Game
{
public:
	Game();
	~Game() {};

private:
	std::vector<Player> _players;
	GameBoard _gameBoard = GameBoard();

	bool _gameOver = false;

public:
	void Run();

	bool GetGameOver();

private:
	void DrawScreen();
	void InitGame();
};

#endif // !GAME_H