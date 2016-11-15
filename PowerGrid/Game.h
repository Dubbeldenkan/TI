#ifndef GAME_H
#define GAME_H

#define NOMINMAX

#include "Board.h"
#include "ResourceMarket.h"
#include "PowerPlantMarket.h"
#include "Player.h"
#include "Draw.h"

#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>

class Game
{
public:
	enum GameSubPhase {initPhase, choosePowerPlant, bid, placePowerPlant, nextPhase};

private:
	static const int MAX_PLAYERS = 6;

	struct Phase2Struct
	{
		int _selectedPowerPlant;
		int _bidForSelectedPowerPlant;
		Player* _lastBiddingPlayer;
		int _nextBid;
		bool _buttonPressed;
		std::vector<Player*> _bidPlayerVector;
	}_phase2Struct;

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

public:
	Game(int, HWND);
	~Game() {};

	void Run();

	int GetCurrentPhase();
	GameSubPhase GetCurrentSubPhase();
	int GetCurrentStep();
	Draw* GetDraw();
	Player* GetPlayerInTurn();
	PowerPlantMarket* GetPowerPlantMarket();

	void IncreaseNextBid(int);
	int GetBidForSelectedPowerPlant();
	int GetPlayerInTurnPosition();

private:
	void SetNextPlayerInTurn(std::vector<Player*>*);
	void RemovePlayerFromTempVector(std::vector<Player*>*);
	void InitPlayers(int);

	void DrawBoard();
	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();
};

#endif // !GAME_H