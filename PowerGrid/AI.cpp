#include "AI.h"

AI::AI(Chromosome* chrom, Game* game, char* playerName)
{
	_chrom = chrom;
	_playerName = playerName;
	_game = game;

}

Player* AI::GetPlayer()
{
	return _player;
}

void AI::SetPlayer(Player* player)
{
	_p2s.powerPlantsValuesSet = false;
	_player = player;
}

char* AI::GetName()
{
	return _playerName;
}

void AI::DoAction()
{
	//TODO _game verkar inte vara definierat här.. Konstigt..
	switch (_game->GetCurrentPhase())
	{
	case 2:
	{
		Phase2();
		break;
	}
	case 3:
	{
		Phase2();
		break;
	}
	case 4:
	{
		Phase4();
		break;
	}
	case 5:
	{
		Phase5();
		break;
	}
	default:
		break;
	}
}

void AI::Phase2()
{
	if (!_p2s.powerPlantsValuesSet)
	{
		for (int index = 0; index < Player::numberOfPowerPlants; index++)
		{
			_p2s.powerPlantValue[index] = CalculateValueOfPowerPlant(_player->GetPowerPlant(index), 0);
		}
	}
	Game::GameSubPhase gameSubPhase = _game->GetCurrentSubPhase();
	PowerPlantMarket* ppm = _game->GetPowerPlantMarket();
	switch (gameSubPhase)
	{
	case Game::choosePowerPlant:
	{
		int bestPos;
		int bestValue = 0;
		for (int index = 0; index < ppm->GetNumberInCurrentMarket(); index++)
		{
			int tempValue = CalculateValueOfPowerPlant(ppm->GetPowerPlantCurrentDeck(index),
				ppm->GetPowerPlantCurrentDeck(index)->GetPowerPlantNumber());
			if (tempValue > bestValue && _player->GetAmountOfElektro() >= 
				ppm->GetPowerPlantCurrentDeck(index)->GetPowerPlantNumber())
			{
				bestValue = tempValue;
				bestPos = index;
			}
		}
		if (bestValue > _chrom->GetPowerPlantLimit())
		{
			_game->GetPlayerInTurn()->SetSelectedPowerPlant(bestPos + 1);
		}
		else
		{
			_player->SetPassed();
		}
		break;
	}
	case Game::bid:
	{
		bool thisIsTheBestPowerPlant = true;
		PowerPlant* powerPlant = ppm->GetPowerPlantCurrentDeck(_game->GetSelectedPowerPlant());
		int latestBid = _game->GetLastBidForSelectedPowerPlant();
		int currentPowerPlantValue = CalculateValueOfPowerPlant(powerPlant, latestBid);

		for (int index = 0; index < ppm->GetNumberInCurrentMarket(); index++)
		{
			int tempValue;
			if (index != _game->GetSelectedPowerPlant())
			{
				tempValue = CalculateValueOfPowerPlant(ppm->GetPowerPlantCurrentDeck(index),
					ppm->GetPowerPlantCurrentDeck(index)->GetPowerPlantNumber());
				if (tempValue < currentPowerPlantValue)
				{
					thisIsTheBestPowerPlant = false;
					break;
				}
			}
		}
		if (currentPowerPlantValue > _chrom->GetPowerPlantLimit() && _player->GetAmountOfElektro() > latestBid &&
			thisIsTheBestPowerPlant)
		{
			//TODO kanske göra så att de inte alltid ökar med ett
			_player->SetBid(latestBid + 1);
		}
		else
		{
			_player->SetPassed();
		}
		break;
	}
	case Game::placePowerPlant:
	{
		int lowestValue = MAXINT;
		int lowestValuePos;
		for (int index = 0; index < Player::numberOfPowerPlants; index++)
		{
			if (_p2s.powerPlantValue[index] < lowestValue)
			{
				lowestValue = _p2s.powerPlantValue[index];
				lowestValuePos = index;
			}
		}
		_game->GetPlayerInTurn()->SetNewPowerPlantPos(lowestValuePos);
		break;
	}
	}
}

int AI::CalculateValueOfPowerPlant(PowerPlant* powerPlant, int cost)
{
	int result = 0;
	if (powerPlant->GetPowerPlantNumber() == 0)
	{
		result = _chrom->GetNoPowerPlantValue();
	}
	else
	{
		if (powerPlant->GetType() == PowerPlant::none)
		{
			result += _chrom->GetNoResourcePowerPlant();
		}
		else
		{
			int diffConsumptionProduction = 0;
			int consumption;
			int production;
			if (powerPlant->GetType() == PowerPlant::coalOrOil)
			{
				production = _game->GetResourceMarket()->GetReSupplyAmount(_game->GetCurrentStep(),
					_game->GetNumberOfPlayers(), ResourceMarket::coal) +
					_game->GetResourceMarket()->GetReSupplyAmount(_game->GetCurrentStep(),
						_game->GetNumberOfPlayers(), ResourceMarket::oil);
				consumption = GetConsumptionForSameTypeForOthers(PowerPlant::coal, _player) +
					GetConsumptionForSameTypeForOthers(PowerPlant::oil, _player);
			}
			else
			{
				
				production = _game->GetResourceMarket()->GetReSupplyAmount(_game->GetNumberOfPlayers(),
					_game->GetCurrentStep(), (ResourceMarket::Resource) powerPlant->GetType());
				consumption = GetConsumptionForSameTypeForOthers(powerPlant->GetType(), _player);
			}
			diffConsumptionProduction = production - consumption;
			result += diffConsumptionProduction*_chrom->GetRareResourceForOthers();
			result -= GetNumberOfSameTypeThis(powerPlant->GetType(), _player)*_chrom->GetRareResourceForPlayer();
		}
		result += powerPlant->GetPowerPlantProduction()*_chrom->GetMoreProduction();
		result -= cost*_chrom->GetPowerPlantCost();
	}
	return result;
}

int AI::GetNumberOfSameTypeThis(PowerPlant::EnergySource energySource, Player* player)
{
	int numberOfPowerPlants = 0;
	for (int plantIndex = 0; plantIndex < Player::numberOfPowerPlants; plantIndex++)
	{
		if (energySource == player->GetPowerPlant(plantIndex)->GetType())
		{
			numberOfPowerPlants++;
		}
	}
	return numberOfPowerPlants;
}

int AI::GetConsumptionForSameTypeForOthers(PowerPlant::EnergySource energySource, Player* player)
{
	int resourceConsumption = 0;
	std::vector<Player*> playerVector = _game->GetPlayerVector();
	for (int index = 0; index < playerVector.size(); index++)
	{
		if (player != playerVector[index])
		{
			for (int plantIndex = 0; plantIndex < Player::numberOfPowerPlants; plantIndex++)
			{
				if (energySource == playerVector[index]->GetPowerPlant(plantIndex)->GetType())
				{
					resourceConsumption += playerVector[index]->GetPowerPlant(plantIndex)->GetPowerPlantConsumption();
				}
			}
		}
	}
	return resourceConsumption;
}

void AI::Phase3()
{
	//TODO
}

void AI::Phase4()
{
	//TODO
}

void AI::Phase5()
{
	//TODO
}