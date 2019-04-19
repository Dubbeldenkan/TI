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
	enum GamePhase { STRATEGY_PHASE, ACTION_PHASE, STATUS_PHASE};

private:
	GamePhase _gamePhase;
	std::vector<Player> _players;
	GameBoard _gameBoard = GameBoard();

	bool _gameOver = false;

public:
	Game();
	~Game() {};

	void Run();

	bool GetGameOver();

private:
	void DrawScreen();
	void InitGame();

	void StrategyPhase();
	void ActionPhase();
	void StatusPhase();
};

#endif // !GAME_H