#ifndef POWER_PLANT_MARKET_H
#define POWER_PLANT_MARKET_H

#include <vector>
#include "PowerPlant.h"

class PowerPlantMarket
{
	std::vector<PowerPlant> _ppDeck;
	std::vector<PowerPlant> _currentMarket;
	std::vector<PowerPlant> _futureMarket;

public:
	PowerPlantMarket();
};
#endif // !POWER_PLANT_MARKET_H