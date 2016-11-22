#ifndef RESOURCE_MARKET_H
#define RESOURCE_MARKET_H

#include "Graphics.h"
#include "Logger.h"

class ResourceMarket
{
public:
	enum GameBoard {USA};
	enum Resource{coal, oil, garbage, uranium};

	static const int MAX_AMOUNT_RESOURCE = 24;
	static const int MAX_AMOUNT_URAN = 12;
private:
	int _numberOfPlayers;
	int _amountOfCoal;
	int _amountOfOil;
	int _amountOfGarbage;
	int _amountOfUranium;

	int _marketSize = 9;

	int _resourceSupplyMatrix[5][3][4] = { { { 3, 2, 1, 1 },{ 4, 2, 2, 1 },{ 3, 4, 3, 1 }},
	{ { 4, 2, 1, 1 }, { 5, 3, 2, 1 }, { 3, 4, 3, 1 } },
	{ { 5, 3, 2, 1 }, { 6, 4, 3, 2 }, { 4, 5, 4, 2 } },
	{ { 5, 4, 3, 2 }, { 7, 5, 3, 3 }, { 5, 6, 5, 2 } },
	{ { 7, 5, 3, 2 }, { 9, 6, 5, 3 }, { 6, 7, 6, 3 } } };

	Logger *_log;

public:
	ResourceMarket() {};
	ResourceMarket(int, GameBoard);
	~ResourceMarket() {};

	int GetPrice(Resource, int);
	void ReSupplyResourceMarket(int);
	int GetSizeOfMarket();
	int GetAmountOfCoal();
	int GetAmountOfOil();
	int GetAmountOfGarbage();
	int GetAmountOfUran();

	int GetResourceAmount(ResourceMarket::Resource);

	int GetCost(int, ResourceMarket::Resource);
	void TransferResources(int, ResourceMarket::Resource);

	void PrintResourceMarketData(int);
private:
	int GetFirstResPos(Resource);
	int GetPriceForPos(Resource, int);
};

#endif // !RESOURCE_MARKET_H