#include "Player.h"

Player::Player(Race::RaceEnum raceType, std::map<TupleInt, MapTile> map)
{
	switch (raceType)
	{
	case Race::BaronyOfLetnev:
		_race = BaronyOfLetnev();
		break;
	default:
		break;
	}
	TIParserNS::ListNode* raceData = TIParserNS::TIParser::ReadFile(_race.GetDataFilePath());
	TIParserNS::ListNode* startPlanets = NULL;
	raceData->GetChild(&startPlanets);
	SetStartPlanets(startPlanets, map);
	//SetStartUnits(raceData);
}

Player::~Player()
{}

//TODO kanske ändra till en pekarpekare (**) till startPlanets
void Player::SetStartPlanets(TIParserNS::ListNode* startPlanets, std::map<TupleInt, MapTile> map)
{
	TIParserNS::ListNode* planet = NULL;
	startPlanets->GetChild(&planet);
	do
	{
		std::map<TupleInt, MapTile>::iterator mapIt;
		std::string planetName = planet->GetData();
		for (mapIt = map.begin(); mapIt != map.end(); ++mapIt)
		{
			bool startPlanetsFound = false;
			std::vector<Planet> planets = mapIt->second.GetPlanets();
			for(std::vector<Planet>::size_type i = 0; i < planets.size(); ++i)
			{
				if (planetName.compare(planets[i].GetName()) == 0)
				{
					_planets.push_back(&planets[i]);
					break;
				}
			}
		}
	} while (!planet->GetNext(&planet));
}
//TODO fortsätt med utritningen av "flaggor" på ägda planeter

void Player::SetStartUnits(TIParserNS::ListNode* ListNode)
{

	for (int numberOfUnits = 0; numberOfUnits < 2; numberOfUnits++)
	{
		_unitMap.insert(std::make_pair(TupleInt(0, 0), GroundForce()));
	}
}