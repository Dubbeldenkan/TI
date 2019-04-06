#include "Player.h"

Player::Player(Race::RaceEnum raceType, Player::Color color, const std::map<TupleInt, MapTile>* map) :
	GameBoardObject()
{
	_color = color;
	switch (raceType)
	{
	case Race::BaronyOfLetnev:
		_race = BaronyOfLetnev();
		break;
	default:
		break;
	}
	TIParserNS::ListNode* raceData = TIParserNS::TIParser::ReadFile(_race.GetDataFilePath());
	raceData->GetChild(&raceData);
	/*TIParserNS::ListNode* startPlanets = NULL;
	raceData->GetNext(&startPlanets);*/
	//TODO planeterna blir inte rätt. 
	SetStartPlanets(raceData, map);
	raceData->GetNext(&raceData);
	SetImage(raceData->GetData(), TupleInt(10, 10)); //TODO ändra så att storleken är rätt. 

	//_graphicalPos = TupleInt(-1, -1);
	//SetStartUnits(raceData);
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
	_unitMap = _unitMap;
	_color = player._color;
	_race = player._race;
	_planets = player._planets;
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

void Player::SetStartUnits(TIParserNS::ListNode* ListNode)
{

	for (int numberOfUnits = 0; numberOfUnits < 2; numberOfUnits++)
	{
		_unitMap.insert(std::make_pair(TupleInt(0, 0), GroundForce()));
	}
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
		break;
	case Player::Black:
		break;
	case Player::Yellow:
		break;
	case Player::Green:
		break;
	case Player::Orange:
		break;
	default:
		break;
	}
	std::map<std::string, const Planet*>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		TupleInt planetPos = it->second->GetGraphicalPos();
		_g->DrawRectangle(planetPos.GetX(), planetPos.GetY(),
			_planetIndicatorSize, _planetIndicatorSize, color);
	}
}