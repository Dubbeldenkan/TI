#include "ManageAI.h"

const int ManageAI::AIPoints[6] = { 6, 4, 2, 1, 0, 0 };
const int ManageAI::chromosomePlacement[12][6] = 
										{ {1 , 2 , 3 , 4 , 5 , 6},
										{7 , 8 , 9 , 10, 11, 12},
										{13, 14, 15, 16, 17, 18},
										{19, 20, 21, 22, 23, 24},
										{25, 26, 27, 28, 29, 30},
										{31, 32, 33, 34, 35, 36},
										{1,   7, 13, 19, 25, 31},
										{2,   8, 14, 20, 26, 32},
										{3,   9, 15, 21, 27, 33},
										{4,  10, 16, 22, 28, 34},
										{5,  11, 17, 23, 29, 35},
										{6,  12, 18, 24, 30, 36} };

ManageAI::ManageAI(Game* game, std::vector<Player*> playerVector, bool createNewChromosomes)
{
	_game = game;
	/*Chromosome chromosome1(5, 2, 3, 6, 0, 0, 2, 4, 5, 7, 3, 1);
	_chromosomeVector.push_back(chromosome1);
	Chromosome chromosome2(5, 8, 2, 1, 9, 2, 1, 3, 4, 7, 3, 5);
	_chromosomeVector.push_back(chromosome2);
	Chromosome chromosome3(1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2);
	_chromosomeVector.push_back(chromosome3);
	Chromosome chromosome4(5, 3, 7, 8, 1, 4, 2, 5, 2, 2, 8, 4);
	_chromosomeVector.push_back(chromosome4);
	Chromosome chromosome5(3, 4, 1, 6, 3, 8, 1, 8, 3, 8, 0, 1);
	_chromosomeVector.push_back(chromosome5);
	Chromosome chromosome6(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
	_chromosomeVector.push_back(chromosome6);*/
	if (createNewChromosomes)
	{
		RandomizeChromosomes();
	}
	else
	{
		//TODO läs data från fil
	}
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
	if (_game->GetCurrentPhase() == 7)
	{
		AssignPointsToAIs();
		SetNewChromosomesToAIs();
		_game->ResetGame();
	}
	else if ((_game->GetCurrentPhase() == 2) && (_game->GetCurrentSubPhase() == Game::initPhase))
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

void ManageAI::RandomizeChromosomes()
{
	for (int index = 0; index < numberOfChromosomes; index++)
	{
		_chromosomeVector.push_back(Chromosome());
		for (int chromIndex = 0; chromIndex < Chromosome::chromSize; chromIndex++)
		{
			int randomValue = RandomValue0_9();
			_chromosomeVector[index].SetGen(chromIndex, randomValue);
		}
	}
}

int ManageAI::RandomValue0_9()
{
	int result = rand() % 10;
	return result;
}

void ManageAI::AssignPointsToAIs()
{
	if (_game->GetGameHasAWinner())
	{
		std::vector<Player*> playerVector = _game->GetPlayerVector();
		for (int playerIndex = 0; playerIndex < playerVector.size(); playerIndex++)
		{
			for (int AIIndex = 0; AIIndex < _AIVector.size(); AIIndex++)
			{
				if (_AIVector[AIIndex].GetPlayer() == playerVector[playerIndex])
				{
					_AIVector[AIIndex].GetChromosome()->AddPoints(AIPoints[playerIndex]);
				}
			}
		}
	}
}

void ManageAI::SetNewChromosomesToAIs()
{
	for (int index = 0; index < _AIVector.size(); index++)
	{
		Chromosome* chrom;
		chrom = &_chromosomeVector[chromosomePlacement[_gameTurn][index]];
		_AIVector[index].SetChromosome(chrom);
	}
}