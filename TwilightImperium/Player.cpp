#include "Player.h"

const std::string Player::_shipIndicatorPath = "Unit/ShipIndicator.png";
const TupleInt Player::_playerMetricFirstPos = TupleInt(40, 90);
const TupleInt Player::_playerMetricDiffPos = TupleInt(65, 0);
const TupleInt Player::_commandCounterPos = TupleInt(290, 25);

PlanetContainer::PlanetContainer(const Planet* planet)
{
	_planet = planet;
}

const Planet* PlanetContainer::GetPlanet() const
{
	return _planet;
}

void PlanetContainer::SetToExhausted()
{
	_exhausted = true;
}

void PlanetContainer::UnsetExhausted()
{
	_exhausted = false;
}

Player::Player(Race::RaceEnum raceType, Player::Color color, const std::map<TupleInt, MapTile>* map, int playerGraphicalPos) :
	GameBoardObject()
{
	_color = color;
	_race = Race::CreateRace(raceType);
	
	TIParserNS::ListNode* raceData = TIParserNS::TIParser::ReadFile(_race.GetDataFilePath());
	raceData->GetChild(&raceData);
	SetStartPlanets(raceData, map);
	raceData->GetNext(&raceData);
	SetPlayerImage(raceData);
	raceData->GetNext(&raceData);
	SetStartUnits(raceData);

	_shipIndicator = _g->LoadImageFromFile(_shipIndicatorPath, _shipIndicatorSize, _shipIndicatorSize);

	_posInPlayerOrder = playerGraphicalPos;
	_graphicalPos = TupleInt(_playerSheetPos.GetX(), _playerSheetPos.GetY() + (_playerSheetSize.GetY()*_posInPlayerOrder));
}

Player& Player::operator=(const Player& player)
{
	CopyPlayer(player);
	return *this;
}

Player::Player(const Player &player) :
	GameBoardObject(player._graphicalPos, player._image)
{
	CopyPlayer(player);
}

void Player::CopyPlayer(const Player& player)
{
	_unitMap = player._unitMap;
	_color = player._color;
	_race = player._race;
	_planets = player._planets;
	_shipIndicator = player._shipIndicator;
	_posInPlayerOrder = player._posInPlayerOrder;
	_image = player._image;
	_graphicalPos = player._graphicalPos;
}

Player::~Player()
{}

void Player::SetStartPlanets(TIParserNS::ListNode* startPlanets, const std::map<TupleInt, MapTile>* gameMap)
{
	TIParserNS::ListNode* planet = NULL;
	startPlanets->GetChild(&planet);
	bool systemFound = false;
	do
	{
		std::map<TupleInt, MapTile>::const_iterator mapIt;
		std::string planetName = planet->GetData();
		for (mapIt = gameMap->begin(); mapIt != gameMap->end(); mapIt++)
		{
			const std::vector<Planet>* systemPlanets = mapIt->second.GetPlanets();
			for(int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
			{
				if (planetName.compare(mapIt->second.GetPlanet(planetCount)->GetName()) == 0)
				{
					_homeSystem = mapIt->first;
					systemFound = true;
					break;
				}
			}
			if (systemFound)
			{
				for (int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
				{
					const Planet* planet = mapIt->second.GetPlanet(planetCount);
					_planets.insert(std::make_pair(planet->GetName(), PlanetContainer(planet)));
				}
				break;
			}
		}
	} while (!planet->GetNext(&planet) && !systemFound);
}

void Player::SetPlayerImage(TIParserNS::ListNode* listNode)
{
	listNode->GetChild(&listNode);
	SetImage(listNode->GetData(), _playerSheetSize);
}

void Player::SetStartUnits(TIParserNS::ListNode* listNode)
{
	listNode->GetChild(&listNode);
	_unitMap.insert(std::pair<TupleInt, UnitStack>(_homeSystem, UnitStack()));
	do
	{
		std::string unitName = listNode->GetData();
		TIParserNS::ListNode* tempNode = NULL;
		listNode->GetChild(&tempNode);
		int numberOfUnits = atoi(tempNode->GetData().c_str());

		_unitMap[_homeSystem].AddUnits(unitName, numberOfUnits);
	} while (!listNode->GetNext(&listNode));
}

void Player::DrawObject()
{
	D3DCOLOR color;
	switch (_color)
	{
	case Player::Red:
		color = GraphicsNS::Graphics::RED;
		break;
	case Player::Blue:
		color = GraphicsNS::Graphics::BLUE;
		break;
	case Player::White:
		color = GraphicsNS::Graphics::WHITE;
		break;
	case Player::Yellow:
		color = GraphicsNS::Graphics::YELLOW;
		break;
	case Player::Green:
		color = GraphicsNS::Graphics::GREEN;
		break;
	case Player::Purple:
		color = GraphicsNS::Graphics::PURPLE;
		break;
	default:
		break;
	}

	DrawPlanetMarkers(color);
	DrawUnits(color);
	DrawPlayerSheet(color);
}

void Player::DrawPlanetMarkers(D3DCOLOR color)
{
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		TupleInt planetPos = it->second.GetPlanet()->GetGraphicalPos();
		_g->DrawRectangle(planetPos.GetX(), planetPos.GetY(),
			_planetIndicatorSize, _planetIndicatorSize, color);
	}
}

void Player::DrawUnits(D3DCOLOR color)
{
	std::map<TupleInt, UnitStack>::iterator it;
	for (it = _unitMap.begin(); it != _unitMap.end(); it++)
	{
		int numberOfShips = it->second.GetSum();
		TupleInt graphicalPos = GameMap::CalculateGraphicalPosForTile(it->first) + _unitPosInTile;
		_g->DrawWithColor(_shipIndicator, graphicalPos.GetX(), graphicalPos.GetY(), color);
		_g->PrintText15(numberOfShips, graphicalPos.GetX() + _shipIndicator->GetXSize(), graphicalPos.GetY(), color);
	}
}

void Player::DrawPlayerSheet(D3DCOLOR color)
{
	_g->Draw(_image, _graphicalPos.GetX(), _graphicalPos.GetY(), _scale);
	_g->PrintText15(_race.GetRaceName(), _graphicalPos.GetX(), _graphicalPos.GetY(), color);
	_g->PrintText15(_commandPool, _graphicalPos.GetX() + _commandCounterPos.GetX(), 
		_graphicalPos.GetY() + _commandCounterPos.GetY(), color);

	TupleInt playerMetricGraphPos = TupleInt(_graphicalPos.GetX() + _playerMetricFirstPos.GetX(), 
		_graphicalPos.GetY() + _playerMetricFirstPos.GetY());
	_g->PrintText15(_tradeGoods, playerMetricGraphPos.GetX(), playerMetricGraphPos.GetY(), color);
	_g->PrintText15(_resources, playerMetricGraphPos.GetX() + _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), color);
	_g->PrintText15(_influence, playerMetricGraphPos.GetX() + 2*_playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), color);
	_g->PrintText15(_strategyAllocation, playerMetricGraphPos.GetX() + 3 * _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), color);
	_g->PrintText15(_fleetSupply, playerMetricGraphPos.GetX() + 4 * _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), color);
}

void Player::PrepareForGameRound()
{
	ResetPlanets();
	_resources = CalculateResources();
	_influence = CalculateInfluence();
	_playerHasPassed = false;
}

void Player::ResetPlanets()
{
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		it->second.UnsetExhausted();
	}
}

int Player::CalculateResources()
{
	int resources = 0;
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		resources += it->second.GetPlanet()->GetResources();
	}
	return resources;
}

int Player::CalculateInfluence()
{
	int influence = 0;
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		influence += it->second.GetPlanet()->GetInfluence();
	}
	return influence;
}

bool Player::TurnIsFinished() const
{
	bool playerIsFinished = false;
	if (_playerHasPassed) // TODO Fixa så att man inte kan göra detta under en pågående omgång
	{
		playerIsFinished = true;
	}
	return playerIsFinished;
}

int Player::GetPosInPlayerOrder() const
{
	return _posInPlayerOrder;
}

bool Player::GetPlayerHasPassed() const
{
	return _playerHasPassed;
}

void Player::Action(GameBoardObject* gbo)
{
	Player* player = static_cast<Player*>(gbo);
	if (this->_objectId == player->GetObjectID())
	{
		_selectedObject = this;
	}
}

void Player::SetToPassed()
{
	_playerHasPassed = true;
}