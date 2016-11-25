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
	//TODO ta bort raden under
	_ppDeck.push_back(PowerPlant(51, PowerPlant::phase3, 0, 0));

	//create the rest of the powerplants
	std::vector<PowerPlant> tempPowerPlantVector;
	tempPowerPlantVector.push_back(PowerPlant(11, PowerPlant::uranium, 1, 2));
	tempPowerPlantVector.push_back(PowerPlant(12, PowerPlant::coalOrOil, 2, 2));
	tempPowerPlantVector.push_back(PowerPlant(14, PowerPlant::garbage, 2, 2));
	tempPowerPlantVector.push_back(PowerPlant(15, PowerPlant::coal, 2, 3));
	tempPowerPlantVector.push_back(PowerPlant(16, PowerPlant::oil, 2, 3));
	tempPowerPlantVector.push_back(PowerPlant(17, PowerPlant::uranium, 1, 2));
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

	while (!tempPowerPlantVector.empty())
	{
		int index = rand() % tempPowerPlantVector.size();
		_ppDeck.push_back(tempPowerPlantVector[index]);
		tempPowerPlantVector.erase(tempPowerPlantVector.begin() + index);
	}
	//TODO ta bort kommentaren
	//_ppDeck.push_back(PowerPlant(51, PowerPlant::phase3, 0, 0));
	_highestNumberedPowerPlant = 51;

	_log = new Logger("PowerPlantMarket");
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
	int soldPowerPlant = _currentMarket[powerPlantPos].GetPowerPlantNumber();
	_currentMarket.erase(_currentMarket.begin() + powerPlantPos);
	_futureMarket.push_back(_ppDeck[0]);
	int newPowerPlant = _ppDeck[0].GetPowerPlantNumber();
	CheckAndSetStep3(&_ppDeck[0]);
	_ppDeck.erase(_ppDeck.begin() + 0);
	int lowestPowerPlantPos = FindLowestPowerPlantNumber(_futureMarket);
	_currentMarket.push_back(_futureMarket[lowestPowerPlantPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestPowerPlantPos);

	std::stringstream ss;
	ss << "Kraftverk  nr " << soldPowerPlant <<
		" såldes och ersattes av " << newPowerPlant;
	_log->Log(ss.str());
}

int PowerPlantMarket::FindLowestPowerPlantNumber(std::vector<PowerPlant> ppVector)
{
	int lowestNumber = _highestNumberedPowerPlant + 1;
	int lowestNumberPos;
	for (int index = 0; index < ppVector.size(); index++)
	{
		if (ppVector[index].GetPowerPlantNumber() < lowestNumber)
		{
			lowestNumber = ppVector[index].GetPowerPlantNumber();
			lowestNumberPos = index;
		}
	}
	return lowestNumberPos;
}

int PowerPlantMarket::FindHighestPowerPlantNumber(std::vector<PowerPlant> ppVector)
{
	int highestNumber = 0;
	int highestNumberPos;
	for (int index = 0; index < ppVector.size(); index++)
	{
		if (ppVector[index].GetPowerPlantNumber() > highestNumber)
		{
			highestNumber = ppVector[index].GetPowerPlantNumber();
			highestNumberPos = index;
		}
	}
	return highestNumberPos;
}

void PowerPlantMarket::RemoveHighestPowerPlant()
{
	int highestPowerPlantPos = FindHighestPowerPlantNumber(_futureMarket);
	int highestNumber = _futureMarket[highestPowerPlantPos].GetPowerPlantNumber();
	_ppDeck.push_back(_futureMarket[highestPowerPlantPos]);
	_futureMarket.erase(_futureMarket.begin() + highestPowerPlantPos);
	_currentMarket.push_back(_ppDeck[0]);
	int newPowerPlant = _ppDeck[0].GetPowerPlantNumber();
	CheckAndSetStep3(&_ppDeck[0]);
	_ppDeck.erase(_ppDeck.begin() + 0);
	highestPowerPlantPos = FindHighestPowerPlantNumber(_currentMarket);
	_futureMarket.push_back(_currentMarket[highestPowerPlantPos]);
	_currentMarket.erase(_currentMarket.begin() + highestPowerPlantPos);

	std::stringstream ss;
	ss << "Det högsta kraftverket, nr " << highestNumber <<
		" lades underst i högen.\nIstället togs nr " << newPowerPlant << " fram.\n\n" <<
		"Nu består den nuvarnade marknaden av: ";
	for (int index = 0; index < _currentMarket.size(); index++)
	{
		ss << _currentMarket[index].GetPowerPlantNumber() << " ";
	}
	if (!_step3)
	{
		ss << "\nDen framtida markaden består av: ";
		for (int index = 0; index < _futureMarket.size(); index++)
		{
			ss << _futureMarket[index].GetPowerPlantNumber() << " ";
		}
	}
	_log->Log(ss.str());
}

void PowerPlantMarket::PrintPowerPlantData(int gameTurn)
{
	std::stringstream ss;
	ss << "\n\nOmgång " << gameTurn;
	_log->Log(ss.str());
}

void PowerPlantMarket::RemoveLowestPowerPlant()
{
	int lowestPowerPlantPosInCurrentMarket = FindLowestPowerPlantNumber(_currentMarket);
	int lowestPowerPlantNumber = _currentMarket[lowestPowerPlantPosInCurrentMarket].GetPowerPlantNumber();

	_currentMarket.erase(_currentMarket.begin() + lowestPowerPlantPosInCurrentMarket);
	_futureMarket.push_back(_ppDeck[0]);
	int newPowerPlant = _ppDeck[0].GetPowerPlantNumber();
	CheckAndSetStep3(&_ppDeck[0]);
	_ppDeck.erase(_ppDeck.begin() + 0);
	int lowestPowerPlantPos = FindLowestPowerPlantNumber(_futureMarket);
	_currentMarket.push_back(_futureMarket[lowestPowerPlantPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestPowerPlantPos);

	std::stringstream ss;
	ss << "Kraftverk  nr " << lowestPowerPlantNumber <<
		" kastades bort och ersattes av " << newPowerPlant;
	_log->Log(ss.str());
}

void PowerPlantMarket::UpdateToStep3()
{
	_numberInCurrentMarket = 6;
	int lowestNumberPos = FindLowestPowerPlantNumber(_futureMarket);
	_currentMarket.push_back(_futureMarket[lowestNumberPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestNumberPos);

	lowestNumberPos = FindLowestPowerPlantNumber(_futureMarket);
	_currentMarket.push_back(_futureMarket[lowestNumberPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestNumberPos);

	lowestNumberPos = FindLowestPowerPlantNumber(_futureMarket);
	_ppDeck.push_back(_futureMarket[lowestNumberPos]);
	_futureMarket.erase(_futureMarket.begin() + lowestNumberPos);

	RemoveLowestPowerPlant();

	std::stringstream ss;
	ss << "Fas3 kortet är borttaget och nu det är nu steg3 \n\n" <<
		"Nu består den nuvarnade marknaden av: ";
	for (int index = 0; index < _currentMarket.size(); index++)
	{
		ss << _currentMarket[index].GetPowerPlantNumber() << " ";
	}
}

void PowerPlantMarket::CheckAndSetStep3(PowerPlant* powerPlant)
{
	if (powerPlant->GetType() == PowerPlant::phase3)
	{
		_step3 = true;
	}
}

bool PowerPlantMarket::GetStep3()
{
	return _step3;
}