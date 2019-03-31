#include "Race.h"

const std::string BaronyOfLetnev::_dataFilePathValue = "BaronyOfLetnev";

Race::Race() 
{}

Race::Race(std::string dataFilePath)
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

std::string Race::GetDataFilePath() const
{
	return _dataFilePath;
}

BaronyOfLetnev::BaronyOfLetnev() : 
	Race(_dataFilePathValue)
{}