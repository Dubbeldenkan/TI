#include "Race.h"

const std::string BaronyOfLetnev::_dataFilePathValue = "BaronyOfLetnev";
const std::string EmiratesOfHacan::_dataFilePathValue = "EmiratesOfHacan";
const std::string FederationOfSol::_dataFilePathValue = "FederationOfSol";
const std::string L1Z1XMindnet::_dataFilePathValue = "L1Z1XMindnet";
const std::string MentakCoalition::_dataFilePathValue = "MentakCoalition";
const std::string NaaluCollective::_dataFilePathValue = "NaaluCollective";

Race::Race() 
{}

Race::Race(const std::string dataFilePath)
{
	_dataFilePath = dataFilePath;
}

Race &Race::operator=(const Race& race)
{
	_dataFilePath = race._dataFilePath;
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

//TODO går detta att göra på ett snyggare sätt?
BaronyOfLetnev::BaronyOfLetnev() : 
	Race(_dataFilePathValue)
{}

EmiratesOfHacan::EmiratesOfHacan() :
	Race(_dataFilePathValue)
{}

FederationOfSol::FederationOfSol() :
	Race(_dataFilePathValue)
{}

L1Z1XMindnet::L1Z1XMindnet() :
	Race(_dataFilePathValue)
{}

MentakCoalition::MentakCoalition() :
	Race(_dataFilePathValue)
{}

NaaluCollective::NaaluCollective() :
	Race(_dataFilePathValue)
{}