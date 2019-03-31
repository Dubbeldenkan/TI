#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "Player.h"
#include "Unit.h"

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
	const int _numberOfPlayers = 1; // TODO ändra till 6;
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