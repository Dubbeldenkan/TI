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
	enum GameSubPhase {initPhase, choosePowerPlant, bid, placePowerPlant, nextPhase, 
		buyResources, buildCities, choosePowerPlantsToProducePower, getPayed};

private:
	static const int MAX_PLAYERS = 6;

	struct Phase2Struct
	{
		int selectedPowerPlant;
		int bidForSelectedPowerPlant;
		Player* lastBiddingPlayer;
		int nextBid;
		bool buttonPressed;
		std::vector<Player*> bidPlayerVector;
		bool allHasPassed;
	}_phase2Struct;

	int _numberOfPlayers;
	int _gameTurn = 1;
	int _gameStep = 1;
	int _gamePhase = 1;

	GameSubPhase _gameSubPhase = initPhase;
	Player* _playerInTurn = 0;

	Board* _board;
	ResourceMarket* _rm;
	PowerPlantMarket _ppm = PowerPlantMarket();
	Draw _draw = Draw();
	std::vector<Player> _pv;
	std::vector<Player*> _tempPlayerVector;

	const static int NumberOfCitiesToStep2[5];
	const static int NumberOfCitiesToEndGame[5];

	bool _gameHasAWinner;

public:
	Game(HWND);
	~Game() {};

	void Run();

	int GetCurrentPhase();
	GameSubPhase GetCurrentSubPhase();
	int GetCurrentStep();
	Draw* GetDraw();
	Player* GetPlayerInTurn();
	PowerPlantMarket* GetPowerPlantMarket();
	ResourceMarket* GetResourceMarket();
	Board* GetBoard();
	int GetNumberOfPlayers();

	void IncreaseNextBid(int);
	int GetBidForSelectedPowerPlant();
	int GetPlayerInTurnPosition();

	std::vector<Player*> GetPlayerVector();
	int GetSelectedPowerPlant();
	int GetLastBidForSelectedPowerPlant();
	int GetNextBid();
	Player* GetLastBiddingPlayer();
	void ResetGame();
	bool GetGameHasAWinner();

	int GetGameTurn();

private:
	void SetNextPlayerInTurn(std::vector<Player*>*, int);
	void RemovePlayerFromTempVector(std::vector<Player*>*, int);
	void InitPlayers();
	Player::Color GetPlayerColorFromString(std::string);
	int GetNewCityCost(char*);
	void PrintDataToLog(int);
	void CheckAndUpdateForStep2();
	void CheckAndUpdateForStep3();
	void CheckIfGameHasEnded();
	void EndGame();

	void DrawBoard();
	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();
};

#endif // !GAME_H