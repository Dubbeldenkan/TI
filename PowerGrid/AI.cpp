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

void AI::ResetP3S()
{
	_p3s.powerPlantsValuesSet = false;
	_p3s.powerPlantIndex = 0;
	_p3s.allPowerPlantsSupplied = false;
	_p3s.consumptionCoal = 0;
	_p3s.consumptionOil = 0;
	_p3s.consumptionGarbage = 0;
	_p3s.consumptionUran = 0;
}

char* AI::GetName()
{
	return _playerName;
}

void AI::DoAction()
{
	if (_player->GetPassed())
	{
		//Do nothing
	}
	else
	{
		switch (_game->GetCurrentPhase())
		{
		case 2:
		{
			Phase2();
			break;
		}
		case 3:
		{
			Phase3();
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
}

void AI::Phase2()
{
	if (!_p2s.powerPlantsValuesSet)
	{
		for (int index = 0; index < Player::numberOfPowerPlants; index++)
		{
			_p2s.powerPlantValue[index] = CalculateValueOfPowerPlant(_player->GetPowerPlant(index), 0);
		}
		_p2s.powerPlantsValuesSet = true;
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
		if (bestValue > _chrom->GetPowerPlantLimit() && 
			_player->GetAmountOfElektro() >= 10 * _chrom->GetSaveMoneyAfterPowerPlantBuy())
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
		if (_game->GetLastBiddingPlayer() != _player)
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
					if (tempValue > currentPowerPlantValue)
					{
						thisIsTheBestPowerPlant = false;
						break;
					}
				}
			}
			if (currentPowerPlantValue > _chrom->GetPowerPlantLimit() && _player->GetAmountOfElektro() > latestBid &&
				thisIsTheBestPowerPlant && _player->GetAmountOfElektro() >= 10*_chrom->GetSaveMoneyAfterPowerPlantBuy())
			{
				//TODO kanske göra så att de inte alltid ökar med ett
				_player->SetBid(latestBid + 1);
			}
			else
			{
				_player->SetPassed();
			}
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
				production = _game->GetResourceMarket()->GetReSupplyAmount(_game->GetNumberOfPlayers(),
					_game->GetCurrentStep(), ResourceMarket::coal) +
					_game->GetResourceMarket()->GetReSupplyAmount(_game->GetNumberOfPlayers(), 
						_game->GetCurrentStep(), ResourceMarket::oil);
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
	if (!_p3s.powerPlantsValuesSet)
	{
		SetP3SPowerPlantVector();
	}
	PowerPlant* pp = _player->GetPowerPlant(_p3s.powerPlantArray[_p3s.powerPlantIndex]);
	if (_p3s.powerPlantIndex >= Player::numberOfPowerPlants)
	{
		_player->SetPassed();
	}
	else if (pp->GetPowerPlantNumber() == 0 || pp->GetType() == PowerPlant::none)
	{
		_p3s.powerPlantIndex++;
	}
	else
	{
		int consumption = pp->GetPowerPlantConsumption();
		PowerPlant::EnergySource energySource = pp->GetType();
		ResourceMarket::Resource resource;
		if (energySource == PowerPlant::coalOrOil)
		{
			if (_game->GetResourceMarket()->GetAmountOfCoal() > _game->GetResourceMarket()->GetAmountOfOil())
			{
				resource = ResourceMarket::coal;
			}
			else
			{
				resource = ResourceMarket::oil;
			}
		}
		else
		{
			resource = (ResourceMarket::Resource) energySource;
		}
		int purchase = consumption - (_player->GetAmountOfResource(energySource) - 
			GetConsumptionForResource(resource));
		int cost = _game->GetResourceMarket()->GetCost(purchase, resource);
		if (purchase <= 0)
		{
			if (_p3s.powerPlantIndex >= Player::numberOfPowerPlants - 1)
			{
				if (_player->GetAmountOfElektro() < 5 * _chrom->GetAggresiveBuyingResources())
				{
					_player->SetPassed();
				}
			}
			_p3s.powerPlantIndex++;
		}
		else if(cost <= _player->GetAmountOfElektro())
		{
			_game->GetPlayerInTurn()->SetBuyResourceStruct(resource, purchase, cost);
			switch (energySource)
			{
			case ResourceMarket::coal:
			{
				_p3s.consumptionCoal += purchase;
				break;
			}
			case ResourceMarket::oil:
			{
				_p3s.consumptionOil += purchase;
				break;
			}
			case ResourceMarket::garbage:
			{
				_p3s.consumptionGarbage += purchase;
				break;
			}
			case ResourceMarket::uranium:
			{
				_p3s.consumptionUran += purchase;
				break;
			}
			}
			_p3s.powerPlantIndex++;
		}
		else
		{
			_player->SetPassed();
		}
	}
}

int AI::GetConsumptionForResource(ResourceMarket::Resource resource)
{
	int result;
	switch (resource)
	{
	case ResourceMarket::coal:
	{
		result = _p3s.consumptionCoal;
	}
	case ResourceMarket::oil:
	{
		result = _p3s.consumptionOil;
	}
	case ResourceMarket::garbage:
	{
		result = _p3s.consumptionGarbage;
	}
	case ResourceMarket::uranium:
	{
		result = _p3s.consumptionUran;
	}
	}
	return result;
}

void AI::SetP3SPowerPlantVector()
{
	int powerPlantProduction[Player::numberOfPowerPlants] = { 0, 0, 0 };
	for (int index = 0; index < Player::numberOfPowerPlants; index++)
	{
		if (_player->GetPowerPlant(index)->GetType() != PowerPlant::none &&
			_player->GetPowerPlant(index)->GetPowerPlantNumber() != 0)
		{
			if (_player->GetPowerPlant(index)->GetPowerPlantConsumption() > powerPlantProduction[0])
			{
				_p3s.powerPlantArray[2] = _p3s.powerPlantArray[1];
				_p3s.powerPlantArray[1] = _p3s.powerPlantArray[0];
				_p3s.powerPlantArray[0] = index;
				powerPlantProduction[2] = powerPlantProduction[1];
				powerPlantProduction[1] = powerPlantProduction[0];
				powerPlantProduction[0] = _player->GetPowerPlant(index)->GetPowerPlantConsumption();
			}
			else if (_player->GetPowerPlant(index)->GetPowerPlantConsumption() > powerPlantProduction[1])
			{
				_p3s.powerPlantArray[2] = _p3s.powerPlantArray[1];
				_p3s.powerPlantArray[1] = index;
				powerPlantProduction[2] = powerPlantProduction[1];
				powerPlantProduction[1] = _player->GetPowerPlant(index)->GetPowerPlantConsumption();
			}
			else
			{
				_p3s.powerPlantArray[2] = index;
				powerPlantProduction[2] = _player->GetPowerPlant(index)->GetPowerPlantConsumption();
			}
		}
	}
	_p3s.powerPlantsValuesSet = true;
}

void AI::Phase4()
{
	if (_player->GetCityVector().size() == 0)
	{
		City* city = FindStartCity();
		if (city->GetCostForFirstFreePos(_game->GetCurrentStep()) <= _player->GetAmountOfElektro())
		{
			_game->GetPlayerInTurn()->SetBuyCityStruct(city->GetName());
		}
		else
		{
			_player->SetPassed();
		}
	}
	else
	{
		if (_chrom->GetMoneyLeftAfterCities()*2 < _player->GetAmountOfElektro() &&
			_player->GetCityVector().size() < _player->GetProducedPower())
		{
			City* city = FindNextCity();
			if (city == NULL)
			{
				_player->SetPassed();
			}
			else
			{
				_game->GetPlayerInTurn()->SetBuyCityStruct(city->GetName());
			}
		}
		else
		{
			_player->SetPassed();
		}
	}
}

City* AI::FindNextCity()
{
	City* cheapestCity = NULL;
	int cheapestCityCost = MAXINT;
	std::vector<City*> cityVector = _player->GetCityVector();
	for (int index = 0; index < cityVector.size(); index++)
	{
		std::vector<City*> neighbourCities = _game->GetBoard()->GetNeighbourCities(cityVector[index]);
		for (int neighbourIndex = 0; neighbourIndex < neighbourCities.size(); neighbourIndex++)
		{
			City* neighbourCity = neighbourCities[neighbourIndex];
			int cityCost = neighbourCity->CheckPriceForCity(_game->GetCurrentStep());
			int buildingCost = _game->GetBoard()->GetCostBetweenTwoCities(cityVector[index]->GetName(),
				neighbourCities[neighbourIndex]->GetName()) + cityCost;
			//TODO gör så att man kan köpa städer som inte ligger precis bredvis en befintlig stad.
			if (buildingCost < cheapestCityCost && cityCost != 0 &&
				!neighbourCity->PlayerAlreadyHasCity((City::Color) _player->GetColor()))
			{
				cheapestCity = neighbourCity;
				cheapestCityCost = buildingCost;
			}
		}
	}
	//TODO ta bort denna
	if (cheapestCity == NULL)
	{
		int temp = 2;
	}
	if (cheapestCityCost > _player->GetAmountOfElektro())
	{
		cheapestCity = NULL;
	}
	return cheapestCity;
}

City* AI::FindStartCity()
{
	bool occupiedCity = true;
	City* city = NULL;
	while (occupiedCity)
	{
		city = _game->GetBoard()->GetRandomCity(_game->GetNumberOfPlayers());
		if (city->GetColorForPos(0) == City::none && _game->GetBoard()->CityIsInUsedRegion(city))
		{
			occupiedCity = false;
		}
	}
	return city;
}

void AI::Phase5()
{
	_player->SetPassed();
}

Chromosome* AI::GetChromosome()
{
	return _chrom;
}

void AI::SetChromosome(Chromosome* chrom)
{
	_chrom = chrom;
}