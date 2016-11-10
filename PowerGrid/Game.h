#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "ResourceMarket.h"
#include "PowerPlantMarket.h"
#include "Player.h"
#include "Draw.h"
#include <vector>
#include <stdlib.h>
#include <time.h> 

class Game
{
	int _numberOfPlayers;
	int _gameTurn = 1;
	int _gameStep = 1;
	int _gamePhase = 1;
	int _playerInTurn = 0;

	Board* _board;
	ResourceMarket* _rm;
	PowerPlantMarket _ppm = PowerPlantMarket();;
	Draw _draw = Draw();
	std::vector<Player> _pv;

public:
	Game(int, Board*, HWND);
	~Game() {};

	void RunTurn();

private:
	void InitPlayers(int);
	void DrawBoard();
	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();
};

#endif // !GAME_H