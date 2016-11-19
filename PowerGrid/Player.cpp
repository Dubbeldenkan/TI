#include "Player.h"

Player::Player(char* name, Color color)
{
	_amountOfElektro = 50;
	_playerName = name;
	_color = color;
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
	return _buyCity.clickedOnNewCity;
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

