#ifndef MANAGE_AI
#define MANAGE_AI

#include "AI.h"
#include "Chromosome.h"
#include "Game.h"
#include <vector>

class ManageAI
{
	std::vector<AI> _AIVector;
	int _numberOfAIs = 0;
	std::vector<Chromosome> _chromosomeVector;
	Game* _game;
	const int numberOfChromosomes = 30;
	const static int AIPoints[6];
	const static int chromosomePlacement[12][6];
	int _generation = 0;
	int _gameTurn = 0;

public:
	ManageAI::ManageAI(Game*, std::vector<Player*>, bool);
	void DoAction();

private:
	AI* FindAIForPlayer(Player*);
	void RandomizeChromosomes();
	int RandomValue0_9();
	void AssignPointsToAIs();
	void SetNewChromosomesToAIs();
};

#endif // !MANAGE_AI