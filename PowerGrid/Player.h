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

public:
	Player(char*, Color);
	~Player() {};
	int GetNumberOfCitiesInNetwork();
	int GetNumberFromHighestPowerPlant();
	char* GetName();
	PowerPlant* GetPowerPlant(int);

};

#endif // !PLAYER_H