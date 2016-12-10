#include "ManageAI.h"

const int ManageAI::AIPoints[maximumNumberOfAIs] = { 6, 4, 2, 1, 0, 0 };
const int ManageAI::chromosomePlacement[numberOfGamesPerGeneration][maximumNumberOfAIs] =
										{ {0, 1 , 2 , 3 , 4 , 5},
										{6,  7 , 8 , 9 , 10, 11},
										{12, 13, 14, 15, 16, 17},
										{18, 19, 20, 21, 22, 23},
										{24, 25, 26, 27, 28, 29},
										{30, 31, 32, 33, 34, 35},
										{0,   6, 12, 18, 24, 30},
										{1,   7, 13, 19, 25, 31},
										{2,   8, 14, 20, 26, 32},
										{3,   9, 15, 21, 27, 33},
										{4,  10, 16, 22, 28, 34},
										{5,  11, 17, 23, 29, 35} };

ManageAI::ManageAI(Game* game, std::vector<Player*> playerVector, bool createNewChromosomes)
{
	_log = new Logger("ManageAI");
	_game = game;
	if (createNewChromosomes)
	{
		RandomizeChromosomes();
	}
	else
	{
		LoadGenerationFromFile();
	}
	for (int index = 0; index < (int) playerVector.size(); index++)
	{
		if (!playerVector[index]->GetHumanPlayer())
		{
			AI ai(&_chromosomeVector[_numberOfAIs], game, (playerVector[index])->GetId());
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
		if (_game->GetNumberOfPlayers() == _AIVector.size())
		{
			SetNewChromosomesToAIs();
			_game->ResetGame();
		}
	}
	else if ((_game->GetCurrentPhase() == 2) && (_game->GetCurrentSubPhase() == Game::initPhase))
	{
		//Set the player after they have changed order in the playerVector
		for (int index = 0; index < (int) playerVector.size(); index++)
		{
			if (!playerVector[index]->GetHumanPlayer())
			{
				for (int aiIndex = 0; aiIndex < _numberOfAIs; aiIndex++)
				{
					if (playerVector[index]->GetId() == _AIVector[aiIndex].GetPlayerId())
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
	std::stringstream ss;
	ss << "Slumpade kromosoner mellan 0 och 9.\n";
	for (int index = 0; index < numberOfChromosomes; index++)
	{
		ss << "Chromosome " << index << ":";
		_chromosomeVector.push_back(Chromosome(index));
		for (int chromIndex = 0; chromIndex < Chromosome::chromSize; chromIndex++)
		{
			int randomValue = RandomValue0_9();
			_chromosomeVector[index].SetGen(chromIndex, randomValue);
			 ss << " " << randomValue;
		}
		ss << "\n";
	}
	_log->Log(ss.str());
}

int ManageAI::RandomValue0_9()
{
	int result = rand() % 10;
	return result;
}

void ManageAI::AssignPointsToAIs()
{
	std::stringstream ss;
	ss << "\nPoäng på kromosonerna för spel nummer " << _gameTurn << " och generation " << _generation <<
		", spelet tog " << _game->GetGameTurn() << " omgångar.\n";
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
					ss << _AIVector[AIIndex].GetChromosome()->GetChromosomeNumber() << ": " << 
						AIPoints[playerIndex] << " poäng lades till, totalt är poängen " <<
						_AIVector[AIIndex].GetChromosome()->GetPoints() << "\n";
					break;
				}
			}
		}
	}
	else
	{
		ss << "Det saknas vinnare för denna omgång.\n";
	}
	_log->Log(ss.str());
}

void ManageAI::SetNewChromosomesToAIs()
{
	_gameTurn++;
	if (_gameTurn == numberOfGamesPerGeneration)
	{
		Chromosome* bestChromArray[maximumNumberOfAIs];
		for (int index = 0; index < maximumNumberOfAIs; index++)
		{
			bestChromArray[index] = new Chromosome();
			bestChromArray[index]->AddPoints(-1);
		}
		for (int chromIndex = 0; chromIndex < numberOfChromosomes; chromIndex++)
		{
			Chromosome* tempChrom = &_chromosomeVector[chromIndex];
			for (int index = 0; index < maximumNumberOfAIs; index++)
			{
				if (tempChrom->GetPoints() > bestChromArray[index]->GetPoints())
				{
					Chromosome* oldChrom = bestChromArray[index];
					bestChromArray[index] = tempChrom;
					tempChrom = oldChrom;
					if (index < (maximumNumberOfAIs - 2) && bestChromArray[index + 1]->GetChromosomeNumber() == -1)
					{
						break;
					}
				}
			}
		}
		for (int index = 0; index < _AIVector.size(); index++)
		{
			Chromosome* chrom;
			chrom = bestChromArray[index];
			_AIVector[index].SetChromosome(chrom);
		}
	}
	else if (_gameTurn > numberOfGamesPerGeneration)
	{
		CreateNewGeneration();
		_gameTurn = 0;
	}
	else
	{
		for (int index = 0; index < _AIVector.size(); index++)
		{
			Chromosome* chrom;
			chrom = &_chromosomeVector[chromosomePlacement[_gameTurn][index]];
			_AIVector[index].SetChromosome(chrom);
		}
	}
}

void ManageAI::CreateNewGeneration()
{
	std::stringstream ss;
	ss << "\nResultat efter generation " << _generation << ": \n";
	for (int index = 0; index < numberOfChromosomes; index++)
	{
		if (_chromosomeVector[index].GetPoints() > 0)
		{
			ss << _chromosomeVector[index].GetChromosomeNumber() << ": " <<
				_chromosomeVector[index].GetPoints() << "\n";
		}
	}
	_log->Log(ss.str());
	std::vector<Chromosome> newGeneration;

	Chromosome* bestChromArray[numberOfSavedChromosomes];
	for (int index = 0; index < numberOfSavedChromosomes; index++)
	{
		bestChromArray[index] = new Chromosome();
		bestChromArray[index]->AddPoints(-1);
	}
	for (int chromIndex = 0; chromIndex < numberOfChromosomes; chromIndex++)
	{
		Chromosome* tempChrom = &_chromosomeVector[chromIndex];
		for (int index = 0; index < numberOfSavedChromosomes; index++)
		{
			if (tempChrom->GetPoints() > bestChromArray[index]->GetPoints())
			{
				Chromosome* oldChrom = bestChromArray[index];
				bestChromArray[index] = tempChrom;
				tempChrom = oldChrom;
				if (index < (numberOfSavedChromosomes - 2) && bestChromArray[index + 1]->GetChromosomeNumber() == -1)
				{
					break;
				}
			}
		}
	}
	std::vector<int> parentsPoints;
	for (int index = 0; index < numberOfSavedChromosomes; index++)
	{
		parentsPoints.push_back(bestChromArray[index]->GetPoints());
		newGeneration.push_back(*bestChromArray[index]);
		newGeneration[index].ResetPoints();
		newGeneration[index].SetChromosomeNumber(index);
	}

	for (int index = numberOfSavedChromosomes; index < numberOfChromosomes; index++)
	{
		std::vector<Chromosome*> chromosomeParents;
		for (int index = 0; index < numberOfSavedChromosomes; index++)
		{
			chromosomeParents.push_back(&newGeneration[index]);
		}
		std::vector<Chromosome*> parentChromosomes = 
			GetParentChromosomes(chromosomeParents, parentsPoints);
		Chromosome* parent1 = parentChromosomes[0];
		Chromosome* parent2 = parentChromosomes[1];
		int randomNumber = rand() % sumOfChance;
		if (randomNumber < chanceForMutation || index == (numberOfChromosomes - 1))
		{
			Chromosome chrom = MutateChromosome(parent1, index);
			newGeneration.push_back(chrom);
		}
		else if (randomNumber < (chanceForMutation + chanceForAverage))
		{
			Chromosome chrom = AverageChromosome(parent1, parent2, index);
			newGeneration.push_back(chrom);
		}
		else
		{
			std::vector<Chromosome> chromVector = CrossoverChromosome(parent1, parent2, index);
			newGeneration.push_back(chromVector[0]);
			newGeneration.push_back(chromVector[1]);
		}
	}

	_generation++;
	std::stringstream ss2;
	ss2 << "\n\nGeneration nummer " << _generation << ":\n";
	for (int index = 0; index < numberOfChromosomes; index++)
	{
		_chromosomeVector[index].ResetPoints();
		ss2 << "Chromosome " << index << ": ";
		for (int genIndex = 0; genIndex < Chromosome::chromSize; genIndex++)
		{
			_chromosomeVector[index].SetGen(genIndex, (newGeneration[index].GetGen(genIndex)));
			ss2 << _chromosomeVector[index].GetGen(genIndex) << " ";
		}
		ss2 << "\n";
	}
	_log->Log(ss2.str());
	SaveGenerationToFile();
}

std::vector<Chromosome*> ManageAI::GetParentChromosomes(std::vector<Chromosome*> parentVector,
	std::vector<int> parentPoints)
{
	int parentPointsSum = 0;
	for (int index = 0; index < numberOfSavedChromosomes; index++)
	{
		parentPointsSum += parentPoints[index];
		parentPoints[index] = parentPointsSum;
	}

	std::vector<Chromosome*> result;
	while (result.size() < 2)
	{
		int parentNumber = rand() % parentPointsSum;
		int index = 0;
		while (parentNumber > parentPoints[index])
		{
			index++;
		}
		if (result.size() == 0)
		{
			result.push_back(parentVector[index]);
		}
		else
		{
			if (result[0] != parentVector[index])
			{
				result.push_back(parentVector[index]);
			}
		}
	}
	return result;
}

Chromosome ManageAI::MutateChromosome(Chromosome* parent, int chromosomeNumber)
{
	Chromosome child = Chromosome(chromosomeNumber);
	for (int index = 0; index < Chromosome::chromSize; index++)
	{
		child.SetGen(index, parent->GetGen(index));
	}
	int numberOfMutatedGenes = rand() % Chromosome::chromSize;
	std::vector<int> mutatedGenes;
	for (int index = 0; index < numberOfMutatedGenes; index++)
	{
		int mutatedGene;
		bool foundNewNumber = false;
		while (!foundNewNumber)
		{
			foundNewNumber = true;
			mutatedGene = rand() % Chromosome::chromSize;
			if (std::find(mutatedGenes.begin(), mutatedGenes.end(),
				mutatedGene) != mutatedGenes.end())
			{
				foundNewNumber = false;
			}
		}
		mutatedGenes.push_back(mutatedGene);
		int mutatedGeneValue = RandomValue0_9();
		child.SetGen(mutatedGene, mutatedGeneValue);
	}
	return child;
}

Chromosome ManageAI::AverageChromosome(Chromosome* firstParent, Chromosome* secondParent, int chromosomeNumber)
{
	Chromosome child = Chromosome(chromosomeNumber);
	for (int index = 0; index < Chromosome::chromSize; index++)
	{
		int genValue = (firstParent->GetGen(index) + secondParent->GetGen(index))/2;
		child.SetGen(index, genValue);
	}
	return child;
}

std::vector<Chromosome> ManageAI::CrossoverChromosome(Chromosome* firstParent, Chromosome* secondParent, 
	int chromosomeNumber)
{
	Chromosome firstChild = Chromosome(chromosomeNumber);
	Chromosome secondChild = Chromosome(chromosomeNumber + 1);
	int secondIndex = rand() % Chromosome::chromSize;
	secondIndex += 1; 
	int firstIndex = rand() % secondIndex;
	for (int index = 0; index < Chromosome::chromSize; index++)
	{
		if (index < firstIndex)
		{
			firstChild.SetGen(index, firstParent->GetGen(index));
			secondChild.SetGen(index, secondParent->GetGen(index));
		}
		else if (index < secondIndex)
		{
			firstChild.SetGen(index, secondParent->GetGen(index));
			secondChild.SetGen(index, firstParent->GetGen(index));
		}
		else
		{
			firstChild.SetGen(index, firstParent->GetGen(index));
			secondChild.SetGen(index, secondParent->GetGen(index));
		}
	}
	std::vector<Chromosome> childVector;
	childVector.push_back(firstChild);
	childVector.push_back(secondChild);
	return childVector;
}

void ManageAI::SaveGenerationToFile()
{
	std::string fileName = "ChromosomeGeneration";
	std::ofstream fs;
	fs.open(fileName, std::fstream::in);

	std::stringstream ss;
	ss << _generation << "\n";

	for(int index = 0; index < numberOfChromosomes; index++)
	{
		for (int genIndex = 0; genIndex < Chromosome::chromSize; genIndex++)
		{
			ss << _chromosomeVector[index].GetGen(genIndex) << " ";
		}
		if (index < numberOfChromosomes - 1)
		{
			ss << "\n";
		}
	}

	fs << ss.str() << std::endl;
	fs.close();
}

void ManageAI::LoadGenerationFromFile()
{
	std::ifstream file("ChromosomeGeneration");

	if (file)
	{
		for (int index = 0; index < numberOfChromosomes; index++)
		{
			_chromosomeVector.push_back(Chromosome(index));
		}
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string line;
		file.close();
		
		//Get generation
		std::getline(buffer, line);

		_generation = std::stoi(line);
		int chromIndex = 0;
		std::stringstream ss;
		ss << "\n\nGeneration nummer " << _generation << ": laddad från fil\n";
		while (std::getline(buffer, line))
		{
			ss << "Chromosome " << chromIndex << ": ";
			for (int index = 0; index < (line.size()/2); index++)
			{
				_chromosomeVector[chromIndex].SetGen(index, line[2*index] - '0');
				ss << _chromosomeVector[chromIndex].GetGen(index) << " ";
			}
			ss << "\n";
			chromIndex++;
		}
		_log->Log(ss.str());
	}
}