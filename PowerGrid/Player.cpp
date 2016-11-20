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
	_powerPlants[_buyPlantStruct.newPowerPlantPos] = *powerPlant;
	_amountOfElektro -= cost;
	_buyPlantStruct.newPowerPlantPos = -1;
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
	switch (_buyResourceStruct.resource)
	{
	case ResourceMarket::coal:
	{
		_amountOfCoal += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		break;
	}
	case ResourceMarket::oil:
	{
		_amountOfOil += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		break;
	}
	case ResourceMarket::garbage:
	{
		_amountOfGarbage += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		break;
	}
	case ResourceMarket::uranium:
	{
		_amountOfUran += _buyResourceStruct.amountOfResource;
		_amountOfElektro -= _buyResourceStruct.cost;
		break;
	}
	default:
		break;
	}
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
	int roomForResource = 0;
	for (int index = 0; index < numberOfPowerPlants; index++)
	{
		if (_powerPlants[index].GetType() == resource)
		{
			roomForResource += _powerPlants[index].GetPowerPlantConsumption()*2;
		}
		else if (_powerPlants[index].GetType() == PowerPlant::coalOrOil && 
			(resource == ResourceMarket::coal || resource == ResourceMarket::oil))
		{
			roomForResource += _powerPlants[index].GetPowerPlantConsumption()*2;
			//TODO fixa så att kol/olja funkar att köpa för
		}
	}
	roomForResource -= GetAmountOfResource(resource);
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

void Player::BuyCity(int cost, City* city)
{
	_amountOfElektro -= cost;
	_cityVector.push_back(city);
	_buyCityStruct.clickedOnNewCity = false;
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
		//TODO lägg till så att man kollar attresurser finns
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
	for (int index = 0; index < _numberOfCitiesInNetwork; index++)
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
}