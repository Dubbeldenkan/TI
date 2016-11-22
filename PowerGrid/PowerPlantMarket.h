#ifndef POWER_PLANT_MARKET_H
#define POWER_PLANT_MARKET_H

#include <vector>
#include "PowerPlant.h"
#include "Logger.h"

class PowerPlantMarket
{
	//TODO g�r s� att denna �ndras till sex
	int _numberInCurrentMarket = 4;
	int _highestNumberedPowerPlant;
	std::vector<PowerPlant> _ppDeck;
	std::vector<PowerPlant> _currentMarket;
	std::vector<PowerPlant> _futureMarket;
	int FindLowestPowerPlantNumber(std::vector<PowerPlant>);
	int FindHighestPowerPlantNumber(std::vector<PowerPlant>);

	Logger *_log;

public:
	PowerPlantMarket();
	~PowerPlantMarket() {};

	PowerPlant* GetPowerPlantCurrentDeck(int);
	PowerPlant* GetPowerPlantFutureDeck(int);
	void RemovePowerPlant(int);
	int GetNumberInCurrentMarket();
	void RemoveHighestPowerPlant();
	void PrintPowerPlantData(int);

};
#endif // !POWER_PLANT_MARKET_H