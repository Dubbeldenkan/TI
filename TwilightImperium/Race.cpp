#include "Race.h"


const std::string BaronyOfLetnev::_raceNameValue = "The Barony of Letnev";
const std::string EmiratesOfHacan::_raceNameValue = "The Emirates of Hacan";
const std::string FederationOfSol::_raceNameValue = "The Federation of Sol";
const std::string L1Z1XMindnet::_raceNameValue = "The L1Z1X Mindnet";
const std::string MentakCoalition::_raceNameValue = "The Mentak Coalition";
const std::string NaaluCollective::_raceNameValue = "The Naalu Collective";

const std::map<std::string, std::string> Race::_dataFilePathMap = Race::CreateRaceNameMap();

Race::Race() 
{}

Race::Race(const std::string raceName)
{
	_raceName = raceName;
}

Race &Race::operator=(const Race& race)
{
	_raceName = race._raceName;
	return *this;
}

Race::~Race()
{}

Race Race::CreateRace(RaceEnum raceEnum)
{
	Race race;
	switch (raceEnum)
	{
	case Race::BaronyOfLetnev:
		race = BaronyOfLetnev::BaronyOfLetnev();
		break;
	case Race::EmiratesOfHacan:
		race = EmiratesOfHacan::EmiratesOfHacan();
		break;
	case Race::FederationOfSol:
		race = FederationOfSol::FederationOfSol();
		break;
	case Race::L1Z1XMindnet:
		race = L1Z1XMindnet::L1Z1XMindnet();
		break;
	case Race::MentakCoalition:
		race = MentakCoalition::MentakCoalition();
		break;
	case Race::NaaluCollective:
		race = NaaluCollective::NaaluCollective();
		break;
	default:
		break;
	}

	return race;
}

std::string Race::GetDataFilePath() const
{
	return _dataFilePathMap.at(_raceName);
}

std::string Race::GetRaceName() const
{
	return _raceName;
}

const std::map<std::string, std::string> Race::CreateRaceNameMap()
{
	std::map<std::string, std::string> map;
	map[BaronyOfLetnev::_raceNameValue] = "BaronyOfLetnev";
	map[EmiratesOfHacan::_raceNameValue] = "EmiratesOfHacan";
	map[FederationOfSol::_raceNameValue] = "FederationOfSol";
	map[L1Z1XMindnet::_raceNameValue] = "L1Z1XMindnet";
	map[MentakCoalition::_raceNameValue] = "MentakCoalition";
	map[NaaluCollective::_raceNameValue] = "NaaluCollective";

	return map;
}

//TODO går detta att göra på ett snyggare sätt?
BaronyOfLetnev::BaronyOfLetnev() : 
	Race(_raceNameValue)
{}

EmiratesOfHacan::EmiratesOfHacan() :
	Race(_raceNameValue)
{}

FederationOfSol::FederationOfSol() :
	Race(_raceNameValue)
{}

L1Z1XMindnet::L1Z1XMindnet() :
	Race(_raceNameValue)
{}

MentakCoalition::MentakCoalition() :
	Race(_raceNameValue)
{}

NaaluCollective::NaaluCollective() :
	Race(_raceNameValue)
{}