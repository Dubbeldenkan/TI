#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Chromosome.h"
#include "Game.h"

class AI
{
	struct Phase2Struct
	{
		int powerPlantValue[Player::numberOfPowerPlants];
		bool powerPlantsValuesSet = false;
	};
	struct Phase3Struct
	{
		int powerPlantArray[Player::numberOfPowerPlants];
		int powerPlantIndex;
		bool powerPlantsValuesSet = false;
		bool allPowerPlantsSupplied = false;
		int consumptionCoal = 0;
		int consumptionOil = 0;
		int consumptionGarbage = 0;
		int consumptionUran = 0;
	};

	Game* _game;
	Player* _player;
	Chromosome* _chrom;
	char* _playerName;
	Phase2Struct _p2s;
	Phase3Struct _p3s;
public:
	AI() {};
	AI(Chromosome*, Game*, char*);
	~AI() {};

	void SetPlayer(Player*);
	Player* GetPlayer();
	char* GetName();

	void DoAction();
	void ResetP3S();
private:
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();

	//phase 2
	int CalculateValueOfPowerPlant(PowerPlant*, int);
	int GetConsumptionForSameTypeForOthers(PowerPlant::EnergySource, Player*);
	int GetNumberOfSameTypeThis(PowerPlant::EnergySource, Player*);
	
	//phase 3
	void SetP3SPowerPlantVector();
	int GetConsumptionForResource(ResourceMarket::Resource);

	//Phase 4
	City* FindStartCity();
	City* FindNextCity();
};

#endif // !AI_H