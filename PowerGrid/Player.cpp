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

/*int Player::GetAmountOfCoal()
{
	return _amountOfCoal;
}

int Player::GetAmountOfOil()
{
	return _amountOfOil;
}

int Player::GetAmountOfGarbage()
{
	return _amountOfGarbage;
}

int Player::GetAmountOfUran()
{
	return _amountOfUran;
}*/

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
	return _selectedPowerPlant;
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
	_selectedPowerPlant = 0;
}

void Player::SetSelectedPowerPlant(int powerPlant)
{
	_selectedPowerPlant = powerPlant;
}

bool Player::NewBid()
{
	return _newBid;
}

void Player::SetBid(int bid)
{
	if (bid <= _amountOfElektro)
	{
		_newBid = true;
	}
}

void Player::ResetBid()
{
	_newBid = false;
}

void Player::AddPowerPlant(PowerPlant* powerPlant, int cost)
{
	_powerPlants[_newPowerPlantPos] = *powerPlant;
	_amountOfElektro -= cost;
	_newPowerPlantPos = -1;
	//TODO remove old powerPlants
}

int Player::GetNewPowerPlantPos()
{
	return _newPowerPlantPos;
}

void Player::SetNewPowerPlantPos(int pos)
{
	_newPowerPlantPos = pos;
}

bool Player::SetResource(ResourceMarket::Resource resource, int amountOfResource, int cost)
{
	bool result = false;
	switch (resource)
	{
	case ResourceMarket::coal:
		if (cost <= _amountOfElektro && RoomForResources(resource) >= amountOfResource)
		{
			_amountOfCoal += amountOfResource;
			_amountOfElektro -= cost;
			result = true;
		}
		break;
	case ResourceMarket::oil:
		if (cost <= _amountOfElektro && RoomForResources(resource) >= amountOfResource)
		{
			_amountOfOil += amountOfResource;
			_amountOfElektro -= cost;
			result = true;
		}
		break;
	case ResourceMarket::garbage:
		if (cost <= _amountOfElektro && RoomForResources(resource) >= amountOfResource)
		{
			_amountOfGarbage += amountOfResource;
			_amountOfElektro -= cost;
			result = true;
		}
		break;
	case ResourceMarket::uranium:
		if (cost <= _amountOfElektro && RoomForResources(resource) >= amountOfResource)
		{
			_amountOfUran += amountOfResource;
			_amountOfElektro -= cost;
			result = true;
		}
		break;
	default:
		break;
	}
	return result;
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
	}
	roomForResource -= GetAmountOfResource(resource);
	return roomForResource;
}

