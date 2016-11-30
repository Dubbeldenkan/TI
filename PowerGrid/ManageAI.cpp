#include "ManageAI.h"

ManageAI::ManageAI(Game* game, std::vector<Player*> playerVector)
{
	_game = game;
	Chromosome chromosome1(1, 2, 3, 6, 4, 5, 2, 4);
	_chromosomeVector.push_back(chromosome1);
	Chromosome chromosome2(5, 8, 2, 1, 9, 2, 1, 3);
	_chromosomeVector.push_back(chromosome2);
	for (int index = 0; index < playerVector.size(); index++)
	{
		if (!playerVector[index]->GetHumanPlayer())
		{
			AI ai(&_chromosomeVector[_numberOfAIs], game, (playerVector[index])->GetName());
			_AIVector.push_back(ai);
			_numberOfAIs++;
		}
	}
}

void ManageAI::DoAction()
{
	std::vector<Player*> playerVector = _game->GetPlayerVector();
	if ((_game->GetCurrentPhase() == 2) && (_game->GetCurrentSubPhase() == Game::initPhase))
	{
		//Set the player after they have changed order in the playerVector
		for (int index = 0; index < playerVector.size(); index++)
		{
			if (!playerVector[index]->GetHumanPlayer())
			{
				for (int aiIndex = 0; aiIndex < _numberOfAIs; aiIndex++)
				{
					if (playerVector[index]->GetName() == _AIVector[aiIndex].GetName())
					{
						_AIVector[aiIndex].SetPlayer(playerVector[index]);
						break;
					}
				}
			}
		}
	}
	else if (_game->GetCurrentPhase() == 3 && _game->GetCurrentSubPhase() == Game::initPhase)
	{
		for (int index = 0; index < _numberOfAIs; index++)
		{
			_AIVector[index].ResetP3S();
			break;
		}
	}
	else
	{
		Player* playerInTurn = _game->GetPlayerInTurn();
		if (!playerInTurn->GetHumanPlayer())
		{
			AI* currentAI = FindAIForPlayer(playerInTurn);
			currentAI->DoAction();
		}
	}
}

AI* ManageAI::FindAIForPlayer(Player* playerInTurn)
{
	AI* tempAI = NULL;
	for (int index = 0; index < _AIVector.size(); index++)
	{
		if (_AIVector[index].GetPlayer() == playerInTurn)
		{
			tempAI = &_AIVector[index];
			break;
		}
	}
	return tempAI;
}