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
	Game* _game;
	Player* _player;
	Chromosome* _chrom;
	char* _playerName;
	Phase2Struct _p2s;
public:
	AI() {};
	AI(Chromosome*, Game*, char*);
	~AI() {};

	void SetPlayer(Player*);
	Player* GetPlayer();
	char* GetName();

	void DoAction();
private:
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();

	int CalculateValueOfPowerPlant(PowerPlant*, int);
	int GetConsumptionForSameTypeForOthers(PowerPlant::EnergySource, Player*);
	int GetNumberOfSameTypeThis(PowerPlant::EnergySource, Player*);
};

#endif // !AI_H