#ifndef POWER_PLANT_MARKET_H
#define POWER_PLANT_MARKET_H

#include <vector>
#include "PowerPlant.h"

class PowerPlantMarket
{
	//TODO g�r s� att denna �ndras till sex
	int _numberInCurrentMarket = 4;
	std::vector<PowerPlant> _ppDeck;
	std::vector<PowerPlant> _currentMarket;
	std::vector<PowerPlant> _futureMarket;

public:
	PowerPlantMarket();
	~PowerPlantMarket() {};

	PowerPlant GetPowerPlantCurrentDeck(int);
	PowerPlant GetPowerPlantFutureDeck(int);
	int GetNumberInCurrentMarket();
};
#endif // !POWER_PLANT_MARKET_H