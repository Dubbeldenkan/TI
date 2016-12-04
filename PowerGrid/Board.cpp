#include "Board.h"

Board::Board()
{};

Board::Board(std::vector<int> usedRegions, char* fileName)
{
	_usedRegions = usedRegions;
	_mapName = fileName;
	InitMap();
}

Board &Board::operator=(const Board& other)
{
	return *this;
}

void Board::InsertCityInDict(char* name, int region, int xPos, int yPos)
{
	City* tempCity = new City(name, region, xPos, yPos);
	_cityDict[name] = tempCity;
}

void Board::InitMap()
{
	//Create cities
	InsertCityInDict("Seattle", 0, 37, 7);
	InsertCityInDict("Portland", 0, 6, 58);
	InsertCityInDict("Boise", 0, 129, 103);
	InsertCityInDict("Billings", 0, 284, 70);
	InsertCityInDict("Cheyenne", 0, 350, 150);
	InsertCityInDict("Denver", 0, 335, 197);
	InsertCityInDict("Omaha", 0, 500, 170);

	InsertCityInDict("Salt Lake City", 1, 200, 180);
	InsertCityInDict("San Fransisco", 1, 7, 220);
	InsertCityInDict("Las Vegas", 1, 150, 250);
	InsertCityInDict("Los Angeles", 1, 68, 295);
	InsertCityInDict("San Diego", 1, 105, 340);
	InsertCityInDict("Phoenix", 1, 210, 320);
	InsertCityInDict("Santa Fe", 1, 320, 280);

	InsertCityInDict("Fargo", 2, 490, 50);
	InsertCityInDict("Duluth", 2, 565, 35);
	InsertCityInDict("Minneapolis", 2, 555, 80);
	InsertCityInDict("Chicago", 2, 630, 155);
	InsertCityInDict("St. Louis", 2, 610, 220);
	InsertCityInDict("Cincinnati", 2, 720, 215);
	InsertCityInDict("Knoxville", 2, 720, 275);

	InsertCityInDict("Kansas City", 3, 520, 220);
	InsertCityInDict("Oklahoma City", 3, 490, 280);
	InsertCityInDict("Memphis", 3, 605, 285);
	InsertCityInDict("Dallas", 3, 500, 340);
	InsertCityInDict("Birmingham", 3, 660, 330);
	InsertCityInDict("Houston", 3, 510, 390);
	InsertCityInDict("New Orleans", 3, 610, 390);

	InsertCityInDict("Detroit", 4, 730, 140);
	InsertCityInDict("Buffalo", 4, 835, 130);
	InsertCityInDict("Pittsburgh", 4, 815, 180);
	InsertCityInDict("Boston", 4, 960, 120);
	InsertCityInDict("New York", 4, 940, 170);
	InsertCityInDict("Philadelphia", 4, 920, 200);
	InsertCityInDict("Washington DC", 4, 950, 230);

	InsertCityInDict("Norfolk", 5, 910, 260);
	InsertCityInDict("Raleigh", 5, 855, 295);
	InsertCityInDict("Atlanta", 5, 930, 315);
	InsertCityInDict("Savannah", 5, 810, 340);
	InsertCityInDict("Jacksonville", 5, 810, 390);
	InsertCityInDict("Tampa", 5, 725, 435);
	InsertCityInDict("Miami", 5, 815, 465);

	//create edges
	//region 0
	_edgeDict["Portland-Seattle"] = 3;
	_edgeDict["Billings-Seattle"] = 9;
	_edgeDict["Boise-Seattle"] = 12;
	
	_edgeDict["Portland-San Fransisco"] = 24;
	_edgeDict["Boise-Portland"] = 13;
	
	_edgeDict["Billings-Boise"] = 12;
	_edgeDict["Boise-San Fransisco"] = 23;
	_edgeDict["Boise-Salt Lake City"] = 8;
	_edgeDict["Boise-Cheyenne"] = 24;

	_edgeDict["Billings-Cheyenne"] = 9;
	_edgeDict["Billings-Fargo"] = 17;
	_edgeDict["Billings-Minneapolis"] = 18;

	_edgeDict["Cheyenne-Denver"] = 0;
	_edgeDict["Cheyenne-Omaha"] = 14;
	_edgeDict["Cheyenne-Minneapolis"] = 18;

	_edgeDict["Denver-Salt Lake City"] = 21;
	_edgeDict["Denver-Santa Fe"] = 13;
	_edgeDict["Denver-Kansas City"] = 16;

	_edgeDict["Minneapolis-Omaha"] = 8;
	_edgeDict["Chicago-Omaha"] = 13;
	_edgeDict["Kansas City-Omaha"] = 8;

	//Region 1
	//San Fransisco
	_edgeDict["San Fransisco-Salt Lake City"] = 27;
	_edgeDict["Las Vegas-San Fransisco"] = 14;
	_edgeDict["Los Angeles-San Fransisco"] = 9;
	
	//Los Angeles
	_edgeDict["Las Vegas-Los Angeles"] = 9;
	_edgeDict["Los Angeles-San Diego"] = 3;

	//Las Vegas
	_edgeDict["Las Vegas-Phoenix"] = 15;
	_edgeDict["Las Vegas-San Diego"] = 9;
	_edgeDict["Las Vegas-Salt Lake City"] = 18;
	_edgeDict["Las Vegas-Santa Fe"] = 27;

	//San Diego
	_edgeDict["Phoenix-San Diego"] = 14;

	//Pheonix
	_edgeDict["Phoenix-Santa Fe"] = 18;

	//Salt Lake City
	_edgeDict["Salt Lake City-Santa Fe"] = 28;

	//Santa Fe
	_edgeDict["Kansas City-Santa Fe"] = 16;
	_edgeDict["Oklahoma City-Santa Fe"] = 15;
	_edgeDict["Dallas-Santa Fe"] = 16;
	_edgeDict["Houston-Santa Fe"] = 21;

	//Region 2
	//Fargo
	_edgeDict["Fargo-Minneapolis"] = 6;
	_edgeDict["Duluth-Fargo"] = 6;

	//Duluth
	_edgeDict["Detroit-Duluth"] = 15;
	_edgeDict["Chicago-Duluth"] = 12;
	_edgeDict["Duluth-Minneapolis"] = 5;

	//Minneapolis
	_edgeDict["Chicago-Minneapolis"] = 8;

	//Chicago
	_edgeDict["Chicago-Kansas City"] = 8;
	_edgeDict["Chicago-St. Louis"] = 10;
	_edgeDict["Chicago-Cincinnati"] = 7;
	_edgeDict["Chicago-Detroit"] = 7;

	//St. Louis
	_edgeDict["Kansas City-St. Louis"] = 6;
	_edgeDict["Memphis-St. Louis"] = 7;
	_edgeDict["Atlanta-St. Louis"] = 12;
	_edgeDict["Cincinnati-St. Louis"] = 12;

	//Cincinnati
	_edgeDict["Cincinnati-Knoxville"] = 6;
	_edgeDict["Cincinnati-Raleigh"] = 15;
	_edgeDict["Cincinnati-Pittsburgh"] = 7;
	_edgeDict["Cincinnati-Detroit"] = 4;

	//Knoxville
	_edgeDict["Atlanta-Knoxville"] = 5;

	//Region 3
	//Kansas city
	_edgeDict["Kansas City-Oklahoma City"] = 8;
	_edgeDict["Kansas City-Memphis"] = 12;

	//Oklahoma City
	_edgeDict["Memphis-Oklahoma City"] = 14;
	_edgeDict["Dallas-Oklahoma City"] = 3;

	//Dallas
	_edgeDict["Dallas-Memphis"] = 12;
	_edgeDict["Dallas-New Orleans"] = 12;
	_edgeDict["Dallas-Houston"] = 5;

	//Houston
	_edgeDict["Houston-New Orleans"] = 8;

	//Memphis
	_edgeDict["Birmingham-Memphis"] = 6;
	_edgeDict["Memphis-New Orleans"] = 7;

	//New Orleans
	_edgeDict["Birmingham-New Orleans"] = 11;
	_edgeDict["Jacksonville-New Orleans"] = 16;

	//Birmingham
	_edgeDict["Atlanta-Birmingham"] = 3;
	_edgeDict["Birmingham-Jacksonville"] = 9;

	//Region 4
	//Detroit
	_edgeDict["Buffalo-Detroit"] = 7;
	_edgeDict["Detroit-Pittsburgh"] = 6;

	//Buffalo
	_edgeDict["Buffalo-Pittsburgh"] = 7;
	_edgeDict["Buffalo-New York"] = 8;

	//Boston
	_edgeDict["Boston-New York"] = 3;

	//New York
	_edgeDict["New York-Philadelphia"] = 0;

	//Philadelphia
	_edgeDict["Philadelphia-Washington DC"] = 3;

	//Washington
	_edgeDict["Pittsburgh-Washington DC"] = 6;
	_edgeDict["Norfolk-Washington DC"] = 5;

	//Region 5
	//Raleigh
	_edgeDict["Norfolk-Raleigh"] = 3;
	_edgeDict["Atlanta-Raleigh"] = 7;
	_edgeDict["Raleigh-Savannah"] = 7;

	//Savannah
	_edgeDict["Atlanta-Savannah"] = 7;
	_edgeDict["Jacksonville-Savannah"] = 0;

	//Tampa
	_edgeDict["Jacksonville-Tampa"] = 4;
	_edgeDict["Miami-Tampa"] = 4;
}

void Board::SetMapImage(Image image)
{
	_mapImage = image;
}

Image* Board::GetMapImage()
{
	return &_mapImage;
}

char* Board::GetMapName()
{
	return _mapName;
}

std::map<std::string, City*>::iterator Board::GetCityDictFirstIterator()
{
	return _cityDict.begin();
}

std::map<std::string, City*>::iterator Board::GetCityDictLastIterator()
{
	return _cityDict.end();
}

std::vector<int> Board::GetRegionsInPlay()
{
	return _usedRegions;
}

bool Board::CityIsInUsedRegion(City* city)
{
	bool result = false;
	for (int index = 0; index < _usedRegions.size(); index++)
	{
		if (city->GetRegion() == _usedRegions[index])
		{
			result = true;
			break;
		}
	}
	return result;
}

City* Board::GetCityFromName(char* name)
{
	return _cityDict[name];
}

Board::GetRoadCostOutput Board::GetRoadCost(std::vector<City*> cityVector, char* cityName)
{
	GetRoadCostOutput result;
	if (cityVector.empty())
	{
		result.cityList = "";
		result.cost = 0;
	}
	else
	{
		struct CityDist
		{
			CityDist(City* cityIn, int distIn, City* parentCityIn)
			{
				city = cityIn;
				dist = distIn;
				parentCity = parentCityIn;
			}
			City* city;
			City* parentCity;
			int dist;
			std::vector<City*> neighbourCities;
			bool searchFinished = false;
		};
		std::vector<CityDist> distVector;
		bool finished = false;
		distVector.push_back(CityDist(GetCityFromName(cityName), 0, NULL));
		int cost;
		int index = 0;
		while (!finished)
		{
			for (int vectorIndex = 0; vectorIndex < cityVector.size(); vectorIndex++)
			{
				if (cityVector[vectorIndex]->GetName() == distVector[index].city->GetName())
				{
					finished = true;
					cost = distVector[index].dist;
					break;
				}
			}
			distVector[index].neighbourCities = GetNeighbourCities(distVector[index].city);
			for (int vectorIndex = 0; vectorIndex < distVector[index].neighbourCities.size(); vectorIndex++)
			{
				bool alreadyExist = false;
				for (int i = 0; i < distVector.size(); i++)
				{
					if (distVector[i].city->GetName() == distVector[index].neighbourCities[vectorIndex]->GetName())
					{
						alreadyExist = true;
						break;
					}
				}
				if (!alreadyExist)
				{
					int cityDist = distVector[index].dist + GetCostBetweenTwoCities(distVector[index].city->GetName(),
						distVector[index].neighbourCities[vectorIndex]->GetName());
					distVector.push_back(CityDist(distVector[index].neighbourCities[vectorIndex],
						cityDist, distVector[index].city));
				}
			}
			distVector[index].searchFinished = true;
			int lowestCost = MAXINT;
			for (int i = 0; i < distVector.size(); i++)
			{
				if (!distVector[i].searchFinished && (lowestCost > distVector[i].dist) && !finished)
				{
					lowestCost = distVector[i].dist;
					index = i;
				}
			}
		}
		std::string cityList = "";
		int cityInOrder = 0;
		CityDist *currentCityDist = &distVector[index];
		bool foundStartCity = false;
		while (!foundStartCity)
		{
			cityList += currentCityDist->city->GetName();
			if (currentCityDist->parentCity == NULL)
			{
				foundStartCity = true;
			}
			else
			{
				cityList += "->";
				for (int i = 0; i < distVector.size(); i++)
				{
					if (distVector[i].city == currentCityDist->parentCity)
					{
						currentCityDist = &distVector[i];
					}
				}
			}
		}
		result.cityList = cityList;
		result.cost = cost;
	}
	return result;
}

std::vector<City*> Board::GetNeighbourCities(City* city)
{
	std::string cityName = city->GetName();
	std::vector<City*> neighbourCities;
	typedef std::map<std::string, int>::iterator it_type;
	for (it_type it = _edgeDict.begin(); it != _edgeDict.end(); it++) 
	{
		std::string mapName = it->first;
		int cityNamePos = mapName.find(cityName);
		if (cityNamePos > -1)
		{
			City* city;
			if (cityNamePos != 0)
			{
				int barPos = mapName.find("-");
				std::string cityNameString = mapName.substr(0, barPos);
				const char* constSecondCityName = cityNameString.c_str();
				char* secondCityName = (char*)constSecondCityName;
				city = GetCityFromName(secondCityName);
			}
			else
			{
				int barPos = mapName.find("-");
				int secondCityNameLength = mapName.size() - barPos;
				std::string cityNameString = mapName.substr(barPos + 1, secondCityNameLength);
				const char* constSecondCityName = cityNameString.c_str();
				char* secondCityName = (char*)constSecondCityName;
				city = GetCityFromName(secondCityName);
			}
			if (CityIsInUsedRegion(city))
			{
				neighbourCities.push_back(city);
			}
		}
	}
	return neighbourCities;
}

int Board::GetCostBetweenTwoCities(char* firstCity, char* secondCity)
{
	bool firstCityFirst = strcmp(firstCity, secondCity) < 0;
	std::string roadName = "";
	if (firstCityFirst)
	{
		roadName = std::string(firstCity) + '-';
		roadName += std::string(secondCity);
	}
	else
	{
		roadName = std::string(secondCity) + '-';
		roadName += std::string(firstCity);
	}
	return _edgeDict[roadName];
}

City* Board::GetRandomCity(int numberOfPlayers)
{
	int numberOfCities = numberOfPlayers*numberOfCitiesInEachRegion;
	int randomNumber = rand() % numberOfCities;
	City* city = NULL;
	typedef std::map<std::string, City*>::iterator it_type;
	int index = 0;
	for (it_type it = _cityDict.begin(); it != _cityDict.end(); it++)
	{
		if (index == randomNumber)
		{
			city = it->second;
			break;
		}
		index++;
	}
	return city;
}

void Board::ResetBoard()
{
	typedef std::map<std::string, City*>::iterator it_type;
	for (it_type it = _cityDict.begin(); it != _cityDict.end(); it++)
	{
		it->second->ResetCity();
	}
}