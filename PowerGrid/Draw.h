#ifndef DRAW_H
#define DRAW_H

#include "Player.h"
#include "Board.h"
#include "ResourceMarket.h"
#include "PowerPlantMarket.h"
#include "Graphics.h"
#include "PowerPlant.h"
#include "City.h"

#include <vector>
#include <string>
#include <algorithm> 

class Draw
{
public:
	struct Pos
	{
		int x;
		int y;
		float s;

		Pos(int xIn, int yIn)
		{
			x = xIn;
			y = yIn;
			s = 0.0;
		}
		Pos(int xIn, int yIn, float sIn)
		{
			x = xIn;
			y = yIn;
			s = sIn;
		}
	};
	struct DrawInput
	{
		Board* board;
		std::vector<Player*> playerVector;
		Player* playerInTurn;
		PowerPlantMarket* powerPlantMarket;
		ResourceMarket* resourceMarket;
		int gamePhase;

		int selectedPowerPlant;
		int currentPowerPlantBiddingPrice;
		Player* lastBiddingPlayer;
		int nextBid;
		bool placePowerPlant;
		std::vector<int> regionsInPlay;
		int gameTurn;
		int gameStep;
	};
private:

	Pos _firstCurrentPlantPos = Pos(600, 530);

	Pos _firstFuturePlantPos = Pos(850, 530);
	Pos _plantDiff = Pos(100, 50);

	Pos _mapPos = Pos(0, 0, 0.5);
	Pos _firstPlayerPos = Pos(1025, 0);
	Pos _playerPowerPlantDiff = Pos(67, 0);
	Pos _firstPlayerPowerPlantPos = Pos(10, 29);
	Pos _playerPosDiff = Pos(0, 65);
	Pos _playerInTurnPos = Pos(1025, 500);
	Pos _infoTextPos = Pos(1025, 550);

	Pos _continueButtonPos = Pos(1050, 400);
	Pos _passButtonPos = Pos(1050, 450);
	Pos _increaseButtonPos = Pos(1200, 400);
	Pos _decreaseButtonPos = Pos(1200, 450);
	Pos _nextBidPos = Pos(1130, 403);

	Pos _firstResourceCoalPos = Pos(2, 532);
	Pos _firstResourceOilPos = Pos(2, 552);
	Pos _firstResourceGarbagePos = Pos(2, 572);
	Pos _firstResourceUranPos = Pos(2, 592);
	Pos _resourceDiff = Pos(21, 0);
	Pos _uranDiff = Pos(63, 42);

	Graphics* _g;
	Image _cityLabel;
	Image _playerLabelRed;
	Image _playerLabelBlue;
	Image _playerLabelGreen;
	Image _playerLabelYellow;
	Image _playerLabelBlack;
	Image _playerLabelPurple;
	Image _redButton;
	Image _blueButton;

	Image _powerPlantCoalImage;
	Image _powerPlantOilImage;
	Image _powerPlantCoalOilImage;
	Image _powerPlantGarbageImage;
	Image _powerPlantUranImage;
	Image _powerPlantEcoImage;

	Image _coalImage;
	Image _oilImage;
	Image _garbageImage;
	Image _uranImage;

	Image _redHouse;
	Image _blueHouse;
	Image _greenHouse;
	Image _purpleHouse;
	Image _yellowHouse;
	Image _blackHouse;

	Image _activeImage;
	Image _inActiveImage;

public:
	Draw() {};
	Draw(HWND*, Board*);
	~Draw() {};

	void DrawWholeBoard(DrawInput*);

	Pos GetFirstCurrentPlantPos();
	Pos GetPlantDiff();
	Pos GetSizeOfPowerPlant();
	Pos GetPassButtonPos();
	Pos GetIncreaseBidButtonPos();
	Pos GetDecreaseBidButtonPos();
	Pos GetBidButtonPos();
	Pos GetFirstPlayerPos();
	Pos GetPlayerDiff();
	Pos GetFirstPlayerPowerPlantPos();
	Pos GetPlayerPowerPlantDiff();

	Pos GetFirstCoalPos();
	Pos GetFirstOilPos();
	Pos GetFirstGarbagePos();
	Pos GetFirstUranPos();
	Pos GetUranDiff();
	Pos GetResourceDiff();
	Pos GetSizeOfResource();

	Pos GetSizeOfCity();

private:
	void DrawPowerPlant(PowerPlant*, int, int);
	void DrawCity(City*);
	void DrawPlayer(Player*, int, int);
	void PrintPlayerInTurn(Player*);
	void DrawBoard(Board*, std::vector<int>);
	void DrawResourceMarket(ResourceMarket*);
	void DrawPowerPlantMarket(PowerPlantMarket*, int);
	void DrawBidButtons(int);
	void DrawButton(Image*, char*, Pos);
	void PrintPlantForSale(PowerPlant*, int, char*);
	void DrawResource(int, ResourceMarket::Resource);
	void PrintText(DrawInput*);
	void PrintHelpText(char*);
	void PrintWinner(DrawInput*);
};

#endif // !DRAW_H