#include "Player.h"

const int Player::GetPayedArray[] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 
105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150};

Player::Player(char* name, Color color, bool humanPlayer)
{
	_amountOfElektro = 50;
	_playerName = name;
	_color = color;
	_humanPlayer = humanPlayer;
	for (int i = 0; i < numberOfPowerPlants; i++)
	{
		_powerPlants[i] = PowerPlant();
	}
	_passed = false;
	_log = new Logger(name);
}

int Player::GetNumberOfCitiesInNetwork()
{
	return _numberOfCitiesInNetwork;
}

int Player::GetNumberFromHighestPowerPlant()
{
	int highestValue = 0;
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		if (_powerPlants[index].GetPowerPlantNumber() > highestValue)
		{
			highestValue = _powerPlants[index].GetPowerPlantNumber();
		}
	}
	return highestValue;
}

char* Player::GetName()
{
	return _playerName;
}

PowerPlant* Player::GetPowerPlant(int index)
{
	return &_powerPlants[index];
}

Player::Color Player::GetColor()
{
	return _color;
}

std::vector<City*> Player::GetCityVector()
{
	return _cityVector;
}

int Player::GetAmountOfResource(ResourceMarket::Resource resource)
{
	int result = 0;
	switch (resource)
	{
	case ResourceMarket::coal:
		result = _amountOfCoal;
		break;
	case ResourceMarket::oil:
		result = _amountOfOil;
		break;
	case ResourceMarket::garbage:
		result = _amountOfGarbage;
		break;
	case ResourceMarket::uranium:
		result = _amountOfUran;
		break;
	default:
		break;
	}
	return result;
}

int Player::GetAmountOfResource(PowerPlant::EnergySource resource)
{
	int result = 0;
	switch (resource)
	{
	case PowerPlant::coal:
		result = _amountOfCoal;
		break;
	case PowerPlant::oil:
		result = _amountOfOil;
		break;
	case PowerPlant::garbage:
		result = _amountOfGarbage;
		break;
	case PowerPlant::uranium:
		result = _amountOfUran;
		break;
	default:
		break;
	}
	return result;
}

int Player::GetAmountOfElektro()
{
	return _amountOfElektro;
}

int Player::GetNumberOfSuppliedCities()
{
	return _numberOfSuppliedCities;
}

int Player::GetSelectedPowerPlant()
{
	return _buyPlantStruct.selectedPowerPlant;
}

bool Player::GetClickedOnNewCity()
{
	return _buyCityStruct.clickedOnNewCity;
}

bool Player::GetPassed()
{
	return _passed;
}

void Player::SetPassed()
{
	_passed = true;
}

void Player::ResetPassed()
{
	_passed = false;
}

void Player::ResetSelectedPowerPlant()
{
	_buyPlantStruct.selectedPowerPlant = 0;
}

void Player::SetSelectedPowerPlant(int powerPlant)
{
	_buyPlantStruct.selectedPowerPlant = powerPlant;
}

bool Player::GetTradeOk()
{
	return _buyResourceStruct.tradeOk;
}

int Player::GetAmountOfResource()
{
	return _buyResourceStruct.amountOfResource;
}

ResourceMarket::Resource Player::GetResourceType()
{
	return _buyResourceStruct.resource;
}

char* Player::GetNewCityName()
{
	return _buyCityStruct.newCityName;
}

bool Player::NewBid()
{
	return _buyPlantStruct.newBid;
}

void Player::SetBid(int bid)
{
	if (bid <= _amountOfElektro)
	{
		_buyPlantStruct.newBid = true;
	}
}

void Player::SetBuyCityStruct(char* cityName)
{
	if (!HaveThatCity(cityName))
	{
		_buyCityStruct.newCityName = cityName;
		_buyCityStruct.clickedOnNewCity = true;
	}
}

void Player::ResetBid()
{
	_buyPlantStruct.newBid = false;
}

void Player::AddPowerPlant(PowerPlant* powerPlant, int cost)
{
	//TODO gör så att man förlorar de resurser man inte längre har plats för
	_powerPlants[_buyPlantStruct.newPowerPlantPos] = *powerPlant;
	_amountOfElektro -= cost;
	_buyPlantStruct.newPowerPlantPos = -1;
	std::stringstream ss;
	ss << "Köpte kraftverk nr " << powerPlant->GetPowerPlantNumber() << " för " << cost << " elektro";
	_log->Log(ss.str());
}

int Player::GetNewPowerPlantPos()
{
	return _buyPlantStruct.newPowerPlantPos;
}

void Player::SetNewPowerPlantPos(int pos)
{
	_buyPlantStruct.newPowerPlantPos = pos;
}

void Player::TransferResources()
{
	char* resource = "";
	switch (_buyResourceStruct.resource)
	{
	case ResourceMarket::coal:
	{
		_amountOfCoal += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		resource = "coal";
		break;
	}
	case ResourceMarket::oil:
	{
		_amountOfOil += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		resource = "oil";
		break;
	}
	case ResourceMarket::garbage:
	{
		_amountOfGarbage += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		resource = "garbage";
		break;
	}
	case ResourceMarket::uranium:
	{
		_amountOfUran += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		resource = "uran";
		break;
	}
	default:
		break;
	}

	std::stringstream ss;
	ss << "Köpte " << _buyResourceStruct.amountOfResource << " " << resource << 
		" för " << _buyResourceStruct.cost << " elektro";
	_log->Log(ss.str());
	
	_buyResourceStruct.tradeOk = false;
}

void Player::SetBuyResourceStruct(ResourceMarket::Resource resource, int amountOfResource, int cost)
{
	_buyResourceStruct.cost = cost;
	_buyResourceStruct.amountOfResource = amountOfResource;
	_buyResourceStruct.resource = resource;
	_buyResourceStruct.tradeOk = ((cost <= _amountOfElektro) && (RoomForResources(resource) >= amountOfResource));
}

int Player::RoomForResources(ResourceMarket::Resource resource)
{
	int roomForCoal = 0;
	int roomForOil = 0;
	int roomForGarbage = 0;
	int roomForUran = 0;
	int roomForCoalOrOil = 0;
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		switch (_powerPlants[index].GetType())
		{
		case PowerPlant::coal:
		{
			roomForCoal += _powerPlants[index].GetPowerPlantConsumption() * 2;
			break;
		}
		case PowerPlant::oil:
		{
			roomForOil += _powerPlants[index].GetPowerPlantConsumption() * 2;
			break;
		}
		case PowerPlant::garbage:
		{
			roomForGarbage += _powerPlants[index].GetPowerPlantConsumption() * 2;
			break;
		}
		case PowerPlant::uranium:
		{
			roomForUran += _powerPlants[index].GetPowerPlantConsumption() * 2;
			break;
		}
		case PowerPlant::coalOrOil:
		{
			roomForCoalOrOil += _powerPlants[index].GetPowerPlantConsumption() * 2;
			break;
		}
		default:
			break;
		}
	}

	int roomForResource;
	switch (resource)
	{
	case ResourceMarket::coal:
		roomForResource = roomForCoal - _amountOfCoal + max(0,
			roomForCoalOrOil - (_amountOfOil - roomForOil));
		break;
	case ResourceMarket::oil:
		roomForResource = roomForOil - _amountOfOil + max(0,
			roomForCoalOrOil - (_amountOfCoal - roomForCoal));
		break;
	case ResourceMarket::garbage:
		roomForResource = roomForGarbage - _amountOfGarbage;
		break;
	case ResourceMarket::uranium:
		roomForResource = roomForUran - _amountOfUran;
		break;
	default:
		break;
	}
	return roomForResource;
}

bool Player::HaveThatCity(char* cityName)
{
	bool result = false;
	for (std::vector<City*>::iterator it = _cityVector.begin(); it != _cityVector.end(); ++it) {
		if (strcmp(cityName, (*it)->GetName()) == 0)
		{
			result = true;
			break;
		}
	}
	return result;
}

bool Player::CanAffordCost(int cost)
{
	return (_amountOfElektro >= cost);
}

void Player::BuyCity(int cost, City* city, std::string cityList)
{
	_amountOfElektro -= cost;
	_cityVector.push_back(city);
	_buyCityStruct.clickedOnNewCity = false;
	std::stringstream ss;
	ss << "Staden " << city->GetName() << " lades till för " << cost << " elektro.";
	ss << " via städerna " << cityList;
	_log->Log(ss.str());
}

void Player::ResetClickedOnNewCity()
{
	_buyCityStruct.clickedOnNewCity = false;
}

bool Player::GetPowerPlantClicked()
{
	return _phase5Struct.clickedPowerPlant;
}

void Player::ResetPowerPlantClicked()
{
	_phase5Struct.clickedPowerPlant = false;
}

void Player::SetPowerPlantClicked(int input)
{
	if (_powerPlants[input].GetPowerPlantNumber() > 0)
	{
		_powerPlants[input].ToggleActive();
	}
	_phase5Struct.clickedPowerPlant = true;
}

void Player::ActiveThePowerPlants()
{
	int tempAmountOfCoal = _amountOfCoal;
	int tempAmountOfOil = _amountOfOil;
	int tempAmountOfGarbage = _amountOfGarbage;
	int tempAmountOfUran = _amountOfUran;
	int* tempPointer = NULL;
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		if (_powerPlants[index].GetPowerPlantNumber() == 0)
		{
			continue;
		}
		switch (_powerPlants[index].GetType())
		{
		case PowerPlant::coal:
		{
			tempPointer = &tempAmountOfCoal;
			break;
		}
		case PowerPlant::oil:
		{
			tempPointer = &tempAmountOfOil;
			break;
		}
		case PowerPlant::garbage:
		{
			tempPointer = &tempAmountOfGarbage;
			break;
		}
		case PowerPlant::uranium:
		{
			tempPointer = &tempAmountOfUran;
			break;
		}
		case PowerPlant::coalOrOil:
		{
			//TODO implementera denna
			tempPointer = &tempAmountOfCoal;
			break;
		}
		}
		if (_powerPlants[index].GetPowerPlantConsumption() <= *tempPointer)
		{
			_powerPlants[index].SetToActive();
			*tempPointer -= _powerPlants[index].GetPowerPlantConsumption();
		}
		else
		{
			_powerPlants[index].SetToInActive();
		}
	}
}

void Player::GetPayed()
{
	_numberOfCitiesInNetwork = _cityVector.size();
	int producedEnergy = 0;
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		if (_powerPlants[index].GetActive())
		{
			producedEnergy += _powerPlants[index].GetPowerPlantProduction();
			switch (_powerPlants[index].GetType())
			{
			case PowerPlant::coal:
			{
				_amountOfCoal -= _powerPlants[index].GetPowerPlantConsumption();
				break;
			}
			case PowerPlant::oil:
			{
				_amountOfOil -= _powerPlants[index].GetPowerPlantConsumption();
				break;
			}
			case PowerPlant::garbage:
			{
				_amountOfGarbage -= _powerPlants[index].GetPowerPlantConsumption();
				break;
			}
			case PowerPlant::uranium:
			{
				_amountOfUran -= _powerPlants[index].GetPowerPlantConsumption();
				break;
			}
			case PowerPlant::coalOrOil:
			{
				//TODO implementera denna
				_amountOfCoal -= _powerPlants[index].GetPowerPlantConsumption();
				break;
			}
			default:
				break;
			}
		}
	}
	_numberOfSuppliedCities = min(producedEnergy, _numberOfCitiesInNetwork);
	_amountOfElektro += GetPayedArray[_numberOfSuppliedCities];
	std::stringstream ss;
	ss << "Tjänade " << GetPayedArray[_numberOfSuppliedCities] << " elektro";
	_log->Log(ss.str());
}

bool Player::GetHumanPlayer()
{
	return _humanPlayer;
}

void Player::PrintPlayerData(int gameTurn)
{
	std::stringstream ss;
	ss << "\nOmgång " << gameTurn << "\nElektro: " << _amountOfElektro << "\nKol: " << _amountOfCoal <<
		"\nOlja: " << _amountOfOil << "\nSopor: " << _amountOfGarbage << "\nUran: " << _amountOfUran <<
		"\nAntal städer i nätverk: " << _numberOfCitiesInNetwork << "\nAntal försörjda städer: " <<
		_numberOfSuppliedCities <<"\nKraftVerk:\n"; 
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		if (_powerPlants[index].GetPowerPlantNumber() != 0)
		{
			ss << _powerPlants[index].GetPowerPlantNumber() << "\n";
		}
	}
	ss << "Städer:\n";
	for (int index = 0; index < _cityVector.size(); index++)
	{
		ss << _cityVector[index]->GetName() << "\n";
	}
	_log->Log(ss.str());
}