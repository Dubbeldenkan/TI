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
	int _chrom[5];
	const int _moreProductionPos = 0;
	const int _noResourcePowerPlantPos = 1;
	const int _rareResourceForOthersPos = 2;
	const int _rareResourceForPlayerPos = 3;
	const int _powerPlantLimitPos = 4;
	const int _noPowerPlantPos = 5;
	const int _powerplantCostPos = 6;
	// 0 Hur gärna vill man köpa nya kraftverk
	// 1 Hur gärna vill man ha miljövänliga kraftverk
	// 2 Hur gärna vill man ha kraftverk som ingen annan har
	// 3 Hur gärna vill man ha ett kraftverk av typ man inte tidigare har

public:
	Chromosome() {};
	Chromosome(int, int, int, int, int, int, int);
	~Chromosome() {};

	//Phase 2
	int GetMoreProduction();
	int GetNoResourcePowerPlant();
	int GetRareResourceForOthers();
	int GetRareResourceForPlayer();
	int GetPowerPlantLimit();
	int GetNoPowerPlantValue();
	int GetPowerPlantCost();
};

#endif // !CHROMOSOME_H