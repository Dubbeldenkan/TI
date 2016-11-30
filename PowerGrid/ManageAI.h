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

public:
	ManageAI::ManageAI(Game*, std::vector<Player*>);
	void DoAction();
	AI* FindAIForPlayer(Player*);
};

#endif // !MANAGE_AI