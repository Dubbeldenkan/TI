#include "Race.h"

const std::string BaronyOfLetnev::_dataFilePathValue = "BaronyOfLetnev";
const std::string EmiratesOfHacan::_dataFilePathValue = "EmiratesOfHacan";
const std::string FederationOfSol::_dataFilePathValue = "FederationOfSol";
const std::string L1Z1XMindnet::_dataFilePathValue = "L1Z1XMindnet";
const std::string MentakCoalition::_dataFilePathValue = "MentakCoalition";
const std::string NaaluCollective::_dataFilePathValue = "NaaluCollective";

const std::string BaronyOfLetnev::_raceNameValue = "The Barony of Letnev";
const std::string EmiratesOfHacan::_raceNameValue = "The Emirates of Hacan";
const std::string FederationOfSol::_raceNameValue = "The Federation of Sol";
const std::string L1Z1XMindnet::_raceNameValue = "The L1Z1X Mindnet";
const std::string MentakCoalition::_raceNameValue = "The Mentak Coalition";
const std::string NaaluCollective::_raceNameValue = "The Naalu Collective";

Race::Race() 
{}

Race::Race(const std::string dataFilePath, const std::string raceName)
{
	_raceName = raceName;
	_dataFilePath = dataFilePath;
}

Race &Race::operator=(const Race& race)
{
	_dataFilePath = race._dataFilePath;
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
	return _dataFilePath;
}

std::string Race::GetRaceName() const
{
	return _raceName;
}

//TODO går detta att göra på ett snyggare sätt?
BaronyOfLetnev::BaronyOfLetnev() : 
	Race(_dataFilePathValue, _raceNameValue)
{}

EmiratesOfHacan::EmiratesOfHacan() :
	Race(_dataFilePathValue, _raceNameValue)
{}

FederationOfSol::FederationOfSol() :
	Race(_dataFilePathValue, _raceNameValue)
{}

L1Z1XMindnet::L1Z1XMindnet() :
	Race(_dataFilePathValue, _raceNameValue)
{}

MentakCoalition::MentakCoalition() :
	Race(_dataFilePathValue, _raceNameValue)
{}

NaaluCollective::NaaluCollective() :
	Race(_dataFilePathValue, _raceNameValue)
{}