#ifndef PLAYER_H
#define PLAYER_H

#include "PowerPlant.h"

class Player
{
public:
	enum Color{red, blue, yellow, black, green, purple};
	const static int numberOfPowerPlants = 3;
private:
	Color _color;
	char* _playerName;
	int _numberOfSuppliedCities = 0;
	int _numberOfCitiesInNetwork = 0;
	int _amountOfElektro;
	PowerPlant _powerPlants[numberOfPowerPlants];

	int _amountOfCoal = 0;
	int _amountOfOil = 0;
	int _amountOfGarbage = 0;
	int _amountOfUran = 0;

	int _selectedPowerPlant = 0;

public:
	Player(char*, Color);
	~Player() {};
	int GetNumberOfCitiesInNetwork();
	int GetNumberOfSuppliedCities();
	int GetNumberFromHighestPowerPlant();
	char* GetName();
	PowerPlant* GetPowerPlant(int);
	Player::Color GetColor();
	int GetAmountOfElektro();
	int GetAmountOfCoal();
	int GetAmountOfOil();
	int GetAmountOfGarbage();
	int GetAmountOfUran();

	int GetSelectedPowerPlant();
	void ResetSelectedPowerPlant();
	void SetSelectedPowerPlant(int);
};

#endif // !PLAYER_H