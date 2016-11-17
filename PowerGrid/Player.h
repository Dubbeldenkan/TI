#ifndef PLAYER_H
#define PLAYER_H

#include "PowerPlant.h"
#include "ResourceMarket.h"

class Player
{
public:
	enum Color{red, blue, yellow, black, green, purple};
	const static int numberOfPowerPlants = 3;
private:
	Color _color;
	char* _playerName;
	bool _passed;
	int _numberOfSuppliedCities = 0;
	int _numberOfCitiesInNetwork = 0;
	int _amountOfElektro;
	PowerPlant _powerPlants[numberOfPowerPlants];

	int _newPowerPlantPos = -1;

	int _amountOfCoal = 0;
	int _amountOfOil = 0;
	int _amountOfGarbage = 0;
	int _amountOfUran = 0;

	int _selectedPowerPlant = 0;

	bool _newBid = false;

	int RoomForResources(ResourceMarket::Resource);

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
	/*int GetAmountOfCoal();
	int GetAmountOfOil();
	int GetAmountOfGarbage();
	int GetAmountOfUran();*/
	int GetAmountOfResource(ResourceMarket::Resource);

	bool GetPassed();
	void SetPassed();
	void ResetPassed();

	bool NewBid();
	void SetBid(int);
	void ResetBid();

	int GetNewPowerPlantPos();
	void SetNewPowerPlantPos(int);

	int GetSelectedPowerPlant();
	void ResetSelectedPowerPlant();
	void SetSelectedPowerPlant(int);

	void AddPowerPlant(PowerPlant*, int);
	bool SetResource(ResourceMarket::Resource, int, int);
};

#endif // !PLAYER_H