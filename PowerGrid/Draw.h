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
	Graphics* _g;
	Image _cityLabel;
	Image _playerLabelRed;
	Image _playerLabelBlue;
	Image _playerLabelGreen;
	Image _playerLabelYellow;
	Image _playerLabelBlack;
	Image _playerLabelPurple;
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

	Pos _mapPos = Pos(0, 0, 0.5);
	Pos _firstPlayerPos = Pos(1025, 0);
	Pos _firstPlayerPowerPlantPos = Pos(10, 10);

public:
	Draw() {};
	Draw(HWND, Board*);
	~Draw() {};

	void DrawWholeBoard(Board*, std::vector<Player*>, PowerPlantMarket*, ResourceMarket*);

private:
	void DrawPowerPlant(PowerPlant*, int, int);
	void DrawCity(City*);
	void DrawPlayer(Player*, int);
	void DrawBoard(Board*);
	void DrawResourceMarket(ResourceMarket*);
	void DrawPowerPlantMarket(PowerPlantMarket*);
};

#endif // !DRAW_H