#ifndef MANAGE_AI
#define MANAGE_AI

#include "AI.h"
#include "Chromosome.h"
#include "Game.h"
#include "Logger.h"
#include <vector>

class ManageAI
{
	std::vector<AI> _AIVector;
	int _numberOfAIs = 0;
	std::vector<Chromosome> _chromosomeVector;
	Game* _game;
	const int numberOfChromosomes = 36;
	const static int maximumNumberOfAIs = 6;
	const static int AIPoints[maximumNumberOfAIs];
	const static int numberOfGamesPerGeneration = 12;
	const static int chromosomePlacement[numberOfGamesPerGeneration][maximumNumberOfAIs];
	int _generation = 0;
	int _gameTurn = 0;

	const static int numberOfSavedChromosomes = 3;

	const static int chanceForMutation = 1;
	const static int chanceForAverage = 5;
	const static int chanceForCrossover = 15;
	const static int sumOfChance = chanceForMutation + chanceForAverage + chanceForCrossover;

	Logger* _log;

public:
	ManageAI::ManageAI(Game*, std::vector<Player*>, bool);
	void DoAction();

private:
	AI* FindAIForPlayer(Player*);
	void RandomizeChromosomes();
	int RandomValue0_9();
	void AssignPointsToAIs();

	void SetNewChromosomesToAIs();
	void CreateNewGeneration();

	Chromosome MutateChromosome(Chromosome*, int);
	Chromosome AverageChromosome(Chromosome*, Chromosome*, int);
	std::vector<Chromosome> CrossoverChromosome(Chromosome*, Chromosome*, int);
	std::vector<Chromosome*> GetParentChromosomes(std::vector<Chromosome*>, std::vector<int>);

	void SaveGenerationToFile();
	void LoadGenerationFromFile();
};

#endif // !MANAGE_AI