#ifndef POWER_PLANT_MARKET_H
#define POWER_PLANT_MARKET_H

#include <vector>
#include "PowerPlant.h"
#include "Logger.h"

class PowerPlantMarket
{
	int _numberInCurrentMarket = 4;
	int _highestNumberedPowerPlant;
	std::vector<PowerPlant> _ppDeck;
	std::vector<PowerPlant> _currentMarket;
	std::vector<PowerPlant> _futureMarket;
	int FindLowestPowerPlantNumber(std::vector<PowerPlant>);
	int FindHighestPowerPlantNumber(std::vector<PowerPlant>);
	bool _step3 = false;

	Logger *_log;

public:
	PowerPlantMarket();
	~PowerPlantMarket() {};

	PowerPlant* GetPowerPlantCurrentDeck(int);
	PowerPlant* GetPowerPlantFutureDeck(int);
	void RemovePowerPlant(int);
	int GetNumberInCurrentMarket();
	void RemoveHighestPowerPlant();
	void RemoveLowestPowerPlant();
	void PrintPowerPlantData(int);
	bool GetStep3();
	void UpdateToStep3();
	bool PowerPlantDeckIsEmpty();
	void ResetPowerPlantMarket();

private:
	void CheckAndSetStep3(PowerPlant*);
	void InitPowerPlantMarket();
};
#endif // !POWER_PLANT_MARKET_H