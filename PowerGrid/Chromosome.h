#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome
{
public:
	struct Phase2Struct
	{

	};
private:
	int chromPoints = 0;
	int _chrom[20];

	//Phase 2
	const int _moreProductionPos = 0;
	const int _noResourcePowerPlantPos = 1;
	const int _rareResourceForOthersPos = 2;
	const int _rareResourceForPlayerPos = 3;
	const int _powerPlantLimitPos = 4;
	const int _noPowerPlantPos = 5;
	const int _powerplantCostPos = 6;

	//Phase 3
	const int _aggressiveBuyingResourcesPos = 7;

public:
	Chromosome() {};
	Chromosome(int, int, int, int, int, int, int, int);
	~Chromosome() {};

	//Phase 2
	int GetMoreProduction();
	int GetNoResourcePowerPlant();
	int GetRareResourceForOthers();
	int GetRareResourceForPlayer();
	int GetPowerPlantLimit();
	int GetNoPowerPlantValue();
	int GetPowerPlantCost();

	//Phase 3
	int GetAggresiveBuyingResources();
};

#endif // !CHROMOSOME_H