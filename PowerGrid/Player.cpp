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