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
};

#endif // !MANAGE_AI