#ifndef PLAYER_H
#define PLAYER_H

#include "PowerPlant.h"
#include "ResourceMarket.h"

class Player
{
public:
	enum Color{red, blue, yellow, black, green, purple};
	const static int numberOfPowerPlants = 3;
	struct BuyResourceStruct
	{
		ResourceMarket::Resource resource;
		int amountOfResource;
		int cost;
		bool tradeOk = false;
	};

	struct BuyPlantStruct
	{
		int selectedPowerPlant = 0;
		bool newBid = false;
		int newPowerPlantPos = -1;
	};

	struct BuyCity
	{
		bool clickedOnNewCity = false;
	};

private:
	Color _color;
	char* _playerName;
	bool _passed;
	int _numberOfSuppliedCities = 0;
	int _numberOfCitiesInNetwork = 0;
	int _amountOfElektro;
	PowerPlant _powerPlants[numberOfPowerPlants];

	int _amountOfCoal = 0;
	int _amountOfOil = 0;
	int _amountOfGarbage = 0;
	int _amountOfUran = 0;

	BuyResourceStruct _buyResourceStruct;
	BuyPlantStruct _buyPlantStruct;
	BuyCity _buyCity;

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
	void SetBuyResourceStruct(ResourceMarket::Resource, int, int);
	void TransferResources();
	
	bool GetTradeOk();
	int GetAmountOfResource();
	ResourceMarket::Resource GetResourceType();

	bool GetClickedOnNewCity();

private:
	int RoomForResources(ResourceMarket::Resource);
};

#endif // !PLAYER_H