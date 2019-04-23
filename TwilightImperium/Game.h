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
	bool _initPhase = true;

	static Player* _currentPlayer;

public:
	Game();
	~Game() {};

	void Run();

	bool GetGameOver();

	static void ClickAction(std::vector<GameBoardObject*>);
private:
	void DrawScreen();
	void InitGame();

	void InitStrategyPhase();
	void InitActionPhase();
	void ActionPhase();
	void InitStatusPhase();
};

#endif // !GAME_H