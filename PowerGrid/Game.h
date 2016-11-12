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
public:
	enum GameSubPhase {initPhase, choosePowerPlant, bid, nextPhase};

private:
	int _numberOfPlayers;
	int _gameTurn = 1;
	int _gameStep = 1;
	int _gamePhase = 1;

	GameSubPhase _gameSubPhase = initPhase;
	Player* _playerInTurn = 0;

	Board _board = Board();
	ResourceMarket* _rm;
	PowerPlantMarket _ppm = PowerPlantMarket();
	Draw _draw = Draw();
	std::vector<Player> _pv;
	std::vector<Player*> _tempPlayerVector;

	int _selectedPowerPlant;

public:
	Game(int, HWND);
	~Game() {};

	void Run();

	int GetCurrentPhase();
	GameSubPhase GetCurrentSubPhase();
	int GetCurrentStep();
	Draw* GetDraw();
	Player* GetPlayerInTurn();

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