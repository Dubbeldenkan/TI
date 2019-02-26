#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "Player.h"

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
	void DrawScreen();

	bool GetGameOver();
	void InitGame();

private:
};

#endif // !GAME_H