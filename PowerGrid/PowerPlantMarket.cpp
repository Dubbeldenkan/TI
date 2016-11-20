#include "PowerPlantMarket.h"

PowerPlantMarket::PowerPlantMarket()
{
	//Prepare current market
	_currentMarket.push_back(PowerPlant(3, PowerPlant::oil, 2, 1));
	_currentMarket.push_back(PowerPlant(4, PowerPlant::coal, 2, 1));
	_currentMarket.push_back(PowerPlant(5, PowerPlant::coalOrOil, 2, 1));
	_currentMarket.push_back(PowerPlant(6, PowerPlant::garbage, 1, 1));

	//prepare future market
	_futureMarket.push_back(PowerPlant(7, PowerPlant::oil, 3, 2));
	_futureMarket.push_back(PowerPlant(8, PowerPlant::coal, 3, 2));
	_futureMarket.push_back(PowerPlant(9, PowerPlant::oil, 1, 1));
	_futureMarket.push_back(PowerPlant(10, PowerPlant::coal, 2, 2));

	_ppDeck.push_back(PowerPlant(13, PowerPlant::none, 0, 1));

	//create the rest of the powerplants
	std::vector<PowerPlant> tempPowerPlantVector;
	tempPowerPlantVector.push_back(PowerPlant(11, PowerPlant::uranium, 1, 2));
	tempPowerPlantVector.push_back(PowerPlant(12, PowerPlant::coalOrOil, 2, 2));
	tempPowerPlantVector.push_back(PowerPlant(14, PowerPlant::garbage, 2, 2));
	tempPowerPlantVector.push_back(PowerPlant(15, PowerPlant::coal, 2, 3));
	tempPowerPlantVector.push_back(PowerPlant(16, PowerPlant::oil, 2, 3));
	tempPowerPlantVector.push_back(PowerPlant(17, PowerPlant::uranium, 2, 2));
	tempPowerPlantVector.push_back(PowerPlant(18, PowerPlant::none, 0, 2));
	tempPowerPlantVector.push_back(PowerPlant(19, PowerPlant::garbage, 2, 3));

	tempPowerPlantVector.push_back(PowerPlant(20, PowerPlant::coal, 3, 5));
	tempPowerPlantVector.push_back(PowerPlant(21, PowerPlant::coalOrOil, 2, 4));
	tempPowerPlantVector.push_back(PowerPlant(22, PowerPlant::none, 0, 2));
	tempPowerPlantVector.push_back(PowerPlant(23, PowerPlant::uranium, 1, 3));
	tempPowerPlantVector.push_back(PowerPlant(24, PowerPlant::garbage, 2, 4));
	tempPowerPlantVector.push_back(PowerPlant(25, PowerPlant::coal, 2, 5));
	tempPowerPlantVector.push_back(PowerPlant(26, PowerPlant::oil, 2, 5));
	tempPowerPlantVector.push_back(PowerPlant(27, PowerPlant::none, 0, 3));
	tempPowerPlantVector.push_back(PowerPlant(28, PowerPlant::uranium, 1, 4));
	tempPowerPlantVector.push_back(PowerPlant(29, PowerPlant::coalOrOil, 1, 4));

	tempPowerPlantVector.push_back(PowerPlant(30, PowerPlant::garbage, 3, 6));
	tempPowerPlantVector.push_back(PowerPlant(31, PowerPlant::coal, 3, 6));
	tempPowerPlantVector.push_back(PowerPlant(32, PowerPlant::oil, 3, 6));
	tempPowerPlantVector.push_back(PowerPlant(33, PowerPlant::none, 0, 4));
	tempPowerPlantVector.push_back(PowerPlant(34, PowerPlant::uranium, 1, 5));
	tempPowerPlantVector.push_back(PowerPlant(35, PowerPlant::oil, 1, 5));
	tempPowerPlantVector.push_back(PowerPlant(36, PowerPlant::coal, 3, 7));
	tempPowerPlantVector.push_back(PowerPlant(37, PowerPlant::none, 0, 4));
	tempPowerPlantVector.push_back(PowerPlant(38, PowerPlant::garbage, 3, 7));
	tempPowerPlantVector.push_back(PowerPlant(39, PowerPlant::uranium, 1, 6));

	tempPowerPlantVector.push_back(PowerPlant(40, PowerPlant::oil, 2, 6));
	tempPowerPlantVector.push_back(PowerPlant(42, PowerPlant::coal, 2, 6));
	tempPowerPlantVector.push_back(PowerPlant(44, PowerPlant::none, 0, 5));
	tempPowerPlantVector.push_back(PowerPlant(46, PowerPlant::coalOrOil, 3, 7));
	tempPowerPlantVector.push_back(PowerPlant(50, PowerPlant::none, 0, 6));

	_highestNumberedPowerPlant = 0;

	while (!tempPowerPlantVector.empty())
	{
		int index = rand() % tempPowerPlantVector.size();
		if (_highestNumberedPowerPlant < tempPowerPlantVector[index].GetPowerPlantNumber())
		{
			_highestNumberedPowerPlant = tempPowerPlantVector[index].GetPowerPlantNumber();
		}
		_ppDeck.push_back(tempPowerPlantVector[index]);
		tempPowerPlantVector.erase(tempPowerPlantVector.begin() + index);
	}

	_ppDeck.push_back(PowerPlant(0, PowerPlant::phase3, 0, 0));
}

PowerPlant* PowerPlantMarket::GetPowerPlantCurrentDeck(int index)
{
	return &_currentMarket[index];
}

PowerPlant* PowerPlantMarket::GetPowerPlantFutureDeck(int index)
{
	return &_futureMarket[index];
}

int PowerPlantMarket::GetNumberInCurrentMarket()
{
	return _numberInCurrentMarket;
}

void PowerPlantMarket::RemovePowerPlant(int powerPlantPos)
{
	_currentMarket.erase(_currentMarket.begin() + powerPlantPos);
	_futureMarket.push_back(_ppDeck[0]);
	_ppDeck.erase(_ppDeck.begin() + 0);
	int lowestPowerPlantPos = FindLowestPowerPlantNumber(_futureMarket);
	_currentMarket.push_back(_futureMarket[lowestPowerPlantPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestPowerPlantPos);
}

int PowerPlantMarket::FindLowestPowerPlantNumber(std::vector<PowerPlant> ppVector)
{
	int lowestNumber = _highestNumberedPowerPlant + 1;
	for (int index = 0; index < ppVector.size(); index++)
	{
		if (ppVector[index].GetPowerPlantNumber() < lowestNumber)
		{
			lowestNumber = index;
		}
	}
	return lowestNumber;
}

int PowerPlantMarket::FindHighestPowerPlantNumber(std::vector<PowerPlant> ppVector)
{
	int highestNumber = 0;
	for (int index = 0; index < ppVector.size(); index++)
	{
		if (ppVector[index].GetPowerPlantNumber() > highestNumber)
		{
			highestNumber = index;
		}
	}
	return highestNumber;
}

void PowerPlantMarket::RemoveHighestPowerPlant()
{
	int highestPowerPlantPos = FindHighestPowerPlantNumber(_futureMarket);
	_ppDeck.push_back(_futureMarket[highestPowerPlantPos]);
	_futureMarket.erase(_futureMarket.begin() + highestPowerPlantPos);
	_currentMarket.push_back(_ppDeck[0]);
	_ppDeck.erase(_ppDeck.begin() + 0);
	highestPowerPlantPos = FindHighestPowerPlantNumber(_currentMarket);
	_futureMarket.push_back(_currentMarket[highestPowerPlantPos]);
	_currentMarket.erase(_currentMarket.begin() + highestPowerPlantPos);
}