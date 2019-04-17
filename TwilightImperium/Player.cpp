#include "Player.h"

const std::string Player::_shipIndicatorPath = "Unit/ShipIndicator.png";

Player::Player(Race::RaceEnum raceType, Player::Color color, const std::map<TupleInt, MapTile>* map) :
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
}

Player::~Player()
{}

void Player::SetStartPlanets(TIParserNS::ListNode* startPlanets, const std::map<TupleInt, MapTile>* map)
{
	TIParserNS::ListNode* planet = NULL;
	startPlanets->GetChild(&planet);
	bool systemFound = false;
	do
	{
		//std::map<TupleInt, MapTile>::iterator mapIt;
		std::string planetName = planet->GetData();
		for (auto const& system : *map)
		{
			const std::vector<Planet>* systemPlanets = system.second.GetPlanets();
			for(int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
			{
				if (planetName.compare(system.second.GetPlanet(planetCount)->GetName()) == 0)
				{
					_homeSystem = system.first;
					systemFound = true;
					break;
				}
			}
			if (systemFound)
			{
				for (int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
				{
					const Planet* planet = system.second.GetPlanet(planetCount);
					_planets.insert(std::make_pair(planet->GetName(), planet));
				}
				break;
			}
		}
	} while (!planet->GetNext(&planet) && !systemFound);
}

void Player::SetPlayerImage(TIParserNS::ListNode* listNode)
{
	listNode->GetChild(&listNode);
	SetImage(listNode->GetData(), TupleInt(10, 10)); //TODO ändra så att storleken är rätt. 
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
}

void Player::DrawPlanetMarkers(D3DCOLOR color)
{
	std::map<std::string, const Planet*>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		TupleInt planetPos = it->second->GetGraphicalPos();
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