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

public:
	ManageAI::ManageAI(Game*, std::vector<Player*>, bool);
	
	void DoAction();
	AI* FindAIForPlayer(Player*);
	void RandomizeChromosomes();
	int RandomValue0_9();
};

#endif // !MANAGE_AI