#include "Chromosome.h"

Chromosome::Chromosome(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8,
	int c9, int c10, int c11, int c12)
{
	//TODO gör konstruktorn snyggare
	_chrom[0] = c1;
	_chrom[1] = c2;
	_chrom[2] = c3;
	_chrom[3] = c4;
	_chrom[4] = c5;
	_chrom[5] = c6;
	_chrom[6] = c7;
	_chrom[7] = c8;
	_chrom[8] = c9;
	_chrom[9] = c10;
	_chrom[10] = c11;
	_chrom[11] = c12;
}

int Chromosome::GetMoreProduction()
{
	return _chrom[_moreProductionPos];
}

int Chromosome::GetNoResourcePowerPlant()
{
	return _chrom[_noResourcePowerPlantPos];
}

int Chromosome::GetRareResourceForOthers()
{
	return _chrom[_rareResourceForOthersPos];
}

int Chromosome::GetRareResourceForPlayer()
{
	return _chrom[_rareResourceForPlayerPos];
}

int Chromosome::GetPowerPlantLimit()
{
	return _chrom[_powerPlantLimitPos];
}

int Chromosome::GetNoPowerPlantValue()
{
	return _chrom[_noPowerPlantPos];
}

int Chromosome::GetPowerPlantCost()
{
	return _chrom[_powerplantCostPos];
}

int Chromosome::GetAggresiveBuyingResources()
{
	return _chrom[_aggressiveBuyingResourcesPos];
}

int Chromosome::GetAggressiveBuyingCity()
{
	return _chrom[_aggressiveBuyingCityPos];
}

int Chromosome::GetChooseCheapestPath()
{
	return _chrom[_chooseCheapestPathPos];
}

int Chromosome::GetMoneyLeftAfterCities()
{
	return _chrom[_moneyLeftAfterBuyingCitiesPos];
}


//TODO not used
int Chromosome::GetNumberOfCitiesMoreThanPower()
{
	return _chrom[_numberOfCitiesMoreThanPowerPos];
}