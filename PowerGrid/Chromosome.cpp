#include "Chromosome.h"

Chromosome::Chromosome(int number)
{
	chromosomeNumber = number;
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

void Chromosome::SetGen(int index, int value)
{
	_chrom[index] = value;
}

void Chromosome::AddPoints(int points)
{
	_chromosomePoints += points;
}

int Chromosome::GetSaveMoneyAfterPowerPlantBuy()
{
	return _chrom[_saveMoneyAfterPowerPlantBuy];
}

int Chromosome::GetPoints()
{
	return _chromosomePoints;
}

int Chromosome::GetChromosomeNumber()
{
	return chromosomeNumber;
}

void Chromosome::ResetPoints()
{
	_chromosomePoints = 0;
}

void Chromosome::SetChromosomeNumber(int value)
{
	chromosomeNumber = value;
}