#include "ManageAI.h"

ManageAI::ManageAI(std::vector<Player> players)
{
	Chromosome chromosome1(1, 2, 3);
	_chromosomeVector.push_back(chromosome1);
	Chromosome chromosome2(5, 8, 2);
	_chromosomeVector.push_back(chromosome2);
	for (int index = 0; index < players.size(); index++)
	{
		if (!players[index].GetHumanPlayer())
		{
			AI ai(_chromosomeVector[_numberOfAIs], &(players[index]));
			_AIVector.push_back(ai);
			_numberOfAIs++;
		}
	}
}

//TODO g�r en funktion som g�r igenom vems tur det �r och k�r om det �r en AI