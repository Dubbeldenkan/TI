#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome
{
public:
	static const int chromSize = 13;
private:
	int _chrom[chromSize];
	int _chromosomePoints = 0;
	int chromosomeNumber = -1;

	//Phase 2
	const int _moreProductionPos = 0;
	const int _noResourcePowerPlantPos = 1;
	const int _rareResourceForOthersPos = 2;
	const int _rareResourceForPlayerPos = 3;
	const int _powerPlantLimitPos = 4;
	const int _noPowerPlantPos = 5;
	const int _powerplantCostPos = 6;
	const int _saveMoneyAfterPowerPlantBuy = 12;

	//Phase 3
	const int _aggressiveBuyingResourcesPos = 7;

	//Phase 4
	const int _aggressiveBuyingCityPos = 8;
	const int _chooseCheapestPathPos = 9;
	const int _moneyLeftAfterBuyingCitiesPos = 10;
	const int _numberOfCitiesMoreThanPowerPos = 11;

public:
	Chromosome() {};
	Chromosome(int);
	~Chromosome() {};

	void SetGen(int, int);
	void AddPoints(int);
	int GetPoints();
	int GetChromosomeNumber();
	void ResetPoints();
	void SetChromosomeNumber(int);

	//Phase 2
	int GetMoreProduction();
	int GetNoResourcePowerPlant();
	int GetRareResourceForOthers();
	int GetRareResourceForPlayer();
	int GetPowerPlantLimit();
	int GetNoPowerPlantValue();
	int GetPowerPlantCost();
	int GetSaveMoneyAfterPowerPlantBuy();

	//Phase 3
	int GetAggresiveBuyingResources();

	//Phase 4
	int GetAggressiveBuyingCity();
	int GetChooseCheapestPath();
	int GetMoneyLeftAfterCities();
	int GetNumberOfCitiesMoreThanPower();
};

#endif // !CHROMOSOME_H