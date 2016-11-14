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
		Board* _board;
		std::vector<Player*> _playerVector;
		Player* _playerInTurn;
		PowerPlantMarket* _powerPlantMarket;
		ResourceMarket* _resourceMarket;
		int _gamePhase;

		int _selectedPowerPlant;
		int _currentPowerPlantBiddingPrice;
		Player* _lastBiddingPlayer;
		int _nextBid;
	};
private:

	Pos _firstCurrentPlantPos = Pos(550, 530);

	Pos _firstFuturePlantPos = Pos(850, 530);
	Pos _plantDiff = Pos(100, 50);

	Pos _mapPos = Pos(0, 0, 0.5);
	Pos _firstPlayerPos = Pos(1025, 0);
	Pos _firstPlayerPowerPlantPos = Pos(10, 29);
	Pos _playerPosDiff = Pos(0, 65);
	Pos _playerInTurnPos = Pos(1025, 500);
	Pos _plantForSalePos = Pos(1025, 550);

	Pos _bidButtonPos = Pos(1050, 400);
	Pos _passButtonPos = Pos(1050, 450);
	Pos _increaseButtonPos = Pos(1200, 400);
	Pos _decreaseButtonPos = Pos(1200, 450);
	Pos _nextBidPos = Pos(1130, 403);

	Graphics* _g;
	Image _cityLabel;
	Image _playerLabelRed;
	Image _playerLabelBlue;
	Image _playerLabelGreen;
	Image _playerLabelYellow;
	Image _playerLabelBlack;
	Image _playerLabelPurple;
	Image _redButton;

	Image _powerPlantCoalImage;
	Image _powerPlantOilImage;
	Image _powerPlantCoalOilImage;
	Image _powerPlantGarbageImage;
	Image _powerPlantUranImage;
	Image _powerPlantEcoImage;

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

private:
	void DrawPowerPlant(PowerPlant*, int, int);
	void DrawCity(City*);
	void DrawPlayer(Player*, int);
	void PrintPlayerInTurn(Player*);
	void DrawBoard(Board*);
	void DrawResourceMarket(ResourceMarket*);
	void DrawPowerPlantMarket(PowerPlantMarket*);
	void DrawBidButtons(int);
	void DrawButton(Image*, char*, Pos);
	void PrintPlantForSale(PowerPlant*, int, char*);
};

#endif // !DRAW_H