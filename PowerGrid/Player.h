#ifndef PLAYER_H
#define PLAYER_H

#include "PowerPlant.h"
#include "ResourceMarket.h"
#include "City.h"
#include <vector>
#include "Logger.h"

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

	struct BuyCityStruct
	{
		bool clickedOnNewCity = false;
		char* newCityName;
	};

	struct Phase5struct
	{
		bool clickedPowerPlant = false;
	};

private:
	Color _color;
	char* _playerName;
	int _numberOfSuppliedCities = 0;
	int _numberOfCitiesInNetwork = 0;
	int _amountOfElektro;
	PowerPlant _powerPlants[numberOfPowerPlants];
	std::vector<City*> _cityVector;
	bool _humanPlayer;
	bool _passed;

	int _amountOfCoal = 0;
	int _amountOfOil = 0;
	int _amountOfGarbage = 0;
	int _amountOfUran = 0;

	const static int GetPayedArray[21];

	BuyResourceStruct _buyResourceStruct;
	BuyPlantStruct _buyPlantStruct;
	BuyCityStruct _buyCityStruct;
	Phase5struct _phase5Struct;

	Logger *_log;

public:
	Player(char*, Color, bool);
	~Player() {};
	int GetNumberOfCitiesInNetwork();
	int GetNumberOfSuppliedCities();
	int GetNumberFromHighestPowerPlant();
	char* GetName();
	PowerPlant* GetPowerPlant(int);
	Player::Color GetColor();
	int GetAmountOfElektro();
	int GetAmountOfResource(ResourceMarket::Resource);
	int GetAmountOfResource(PowerPlant::EnergySource);

	bool GetPassed();
	void SetPassed();
	void ResetPassed();
	bool GetHumanPlayer();
	void PrintPlayerData(int);

	//Phase 2
	bool NewBid();
	void SetBid(int);
	void ResetBid();
	int GetNewPowerPlantPos();
	void SetNewPowerPlantPos(int);
	int GetSelectedPowerPlant();
	void ResetSelectedPowerPlant();
	void SetSelectedPowerPlant(int);
	void AddPowerPlant(PowerPlant*, int);
	
	//Phase 3
	void SetBuyResourceStruct(ResourceMarket::Resource, int, int);
	void TransferResources();
	bool GetTradeOk();
	int GetAmountOfResource();
	ResourceMarket::Resource GetResourceType();

	//Phase 4
	bool GetClickedOnNewCity();
	void SetBuyCityStruct(char*);
	char* GetNewCityName();
	bool CanAffordCost(int);
	void BuyCity(int, City*, std::string);
	void ResetClickedOnNewCity();
	std::vector<City*> GetCityVector();

	//Phase 5
	bool GetPowerPlantClicked();
	void ResetPowerPlantClicked();
	void SetPowerPlantClicked(int);
	void ActiveThePowerPlants();
	void GetPayed();

private:
	int RoomForResources(ResourceMarket::Resource);
	bool HaveThatCity(char*);
};

#endif // !PLAYER_H