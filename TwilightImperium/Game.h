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

	static bool _initNewGame;
	static bool _saveGame;
	static bool _loadGame;

public:
	Game();
	~Game() {};

	void Run();

	bool GetGameOver();
	static void SetInitNewGame();
	static void SetSaveGame();
	static void SetLoadGame();

	static void MouseClicked(TupleInt);
	static void MouseMoved(TupleInt);
private:
	void DrawScreen();
	void InitGame();

	void InitStrategyPhase();
	void StrategyPhase();
	void InitActionPhase();
	void ActionPhase();
	void InitStatusPhase();
	void StatusPhase();
};

#endif // !GAME_H