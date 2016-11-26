#include "ManageAI.h"

ManageAI::ManageAI(Game* game, std::vector<Player*> playerVector)
{
	_game = game;
	Chromosome chromosome1(1, 2, 3);
	_chromosomeVector.push_back(chromosome1);
	Chromosome chromosome2(5, 8, 2);
	_chromosomeVector.push_back(chromosome2);
	for (int index = 0; index < playerVector.size(); index++)
	{
		if (!playerVector[index]->GetHumanPlayer())
		{
			AI ai(_chromosomeVector[_numberOfAIs], (playerVector[index]));
			_AIVector.push_back(ai);
			_numberOfAIs++;
		}
	}
}

void ManageAI::DoAction()
{
	Player* playerInTurn = _game->GetPlayerInTurn();
	if (!playerInTurn->GetHumanPlayer())
	{
		AI* currentAI = FindAI(playerInTurn);
	}
}

AI* ManageAI::FindAI(Player* playerInTurn)
{
	//TODO returnera korrekr AI
	AI* ai = new AI();
	return ai;
}