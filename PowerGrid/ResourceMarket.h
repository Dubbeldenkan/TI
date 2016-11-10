#ifndef RESOURCE_MARKET_H
#define RESOURCE_MARKET_H

#include "Graphics.h"

class ResourceMarket
{
public:
	enum GameBoard {USA};
	enum Resource{coal, oil, garbage, uranium};
private:
	const int MAX_AMOUNT_RESOURCE = 24;
	const int MAX_AMOUNT_URAN = 12;
	int _numberOfPlayers;
	int _amountOfCoal;
	int _amountOfOil;
	int _amountOfGarbage;
	int _amountOfUranium;

	int resourceSupplyMatrix[5][3][4] = { { { 3, 2, 1, 1 },{ 4, 2, 2, 1 },{ 3, 4, 3, 1 }},
	{ { 4, 2, 1, 1 }, { 5, 3, 2, 1 }, { 3, 4, 3, 1 } },
	{ { 5, 3, 2, 1 }, { 6, 4, 3, 2 }, { 4, 5, 4, 2 } },
	{ { 5, 4, 3, 2 }, { 7, 5, 3, 3 }, { 5, 6, 5, 2 } },
	{ { 7, 5, 3, 2 }, { 9, 6, 5, 3 }, { 6, 7, 6, 3 } } };

public:
	ResourceMarket() {};
	ResourceMarket(int, GameBoard);
	~ResourceMarket() {};

	int getPrice(Resource, int);
	void reSupplyResourceMarket(int);
private:
	int getFirstResPos(Resource);
	int getPriceForPos(Resource, int);
};

#endif // !RESOURCE_MARKET_H