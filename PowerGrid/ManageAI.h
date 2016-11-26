#ifndef MANAGE_AI
#define MANAGE_AI

#include "AI.h"
#include "Chromosome.h"
#include <vector>

class ManageAI
{
	std::vector<AI> _AIVector;
	int _numberOfAIs = 0;
	std::vector<Chromosome> _chromosomeVector;

public:
	ManageAI::ManageAI(std::vector<Player>);
};

#endif // !MANAGE_AI