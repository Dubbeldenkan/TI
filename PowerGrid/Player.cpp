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

int Player::GetAmountOfCoal()
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

void Player::ResetSelectedPowerPlant()
{
	_selectedPowerPlant = 0;
}