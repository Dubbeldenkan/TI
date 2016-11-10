#include "Board.h"

Board::Board(bool region1Used, bool region2Used, bool region3Used,
	bool region4Used, bool region5Used, bool region6Used, char* fileName)
{
	_usedRegions[0] = region1Used;
	_usedRegions[1] = region2Used;
	_usedRegions[2] = region3Used;
	_usedRegions[3] = region4Used;
	_usedRegions[4] = region5Used;
	_usedRegions[5] = region6Used;

	_mapName = fileName;
	InitMap();
}

void Board::InsertCityInDict(char* name, int region, int xPos, int yPos)
{
	City* tempCity = new City(name, region, xPos, yPos);
	cityDict[name] = tempCity;
}

void Board::InitMap()
{
	//Create cities
	InsertCityInDict("Seattle", 0, 37, 7);
	/*InsertCityInDict("Portland", 0);
	InsertCityInDict("Boise", 0);
	InsertCityInDict("Billings", 0);
	InsertCityInDict("Cheyenne", 0);
	InsertCityInDict("Denver", 0);
	InsertCityInDict("Omaha", 0);

	InsertCityInDict("Salt Lake City", 1);
	InsertCityInDict("San Fransisco", 1);
	InsertCityInDict("Las Vegas", 1);
	InsertCityInDict("Los Angeles", 1);
	InsertCityInDict("San Diego", 1);
	InsertCityInDict("Phoenix", 1);
	InsertCityInDict("Santa Fe", 1);

	InsertCityInDict("Fargo", 2);
	InsertCityInDict("Duluth", 2);
	InsertCityInDict("Minneapolis", 2);
	InsertCityInDict("Chicago", 2);
	InsertCityInDict("St. Louis", 2);
	InsertCityInDict("Cincinnati", 2);
	InsertCityInDict("Knoxville", 2);

	InsertCityInDict("Kansas City", 3);
	InsertCityInDict("Oklahoma City", 3);
	InsertCityInDict("Memphis", 3);
	InsertCityInDict("Dallas", 3);
	InsertCityInDict("Birmingham", 3);
	InsertCityInDict("Houston", 3);
	InsertCityInDict("New Orleans", 3);

	InsertCityInDict("Detroit", 4);
	InsertCityInDict("Buffalo", 4);
	InsertCityInDict("Pittsburgh", 4);
	InsertCityInDict("Boston", 4);
	InsertCityInDict("New York", 4);
	InsertCityInDict("Philadelphia", 4);
	InsertCityInDict("Washington DC", 4);

	InsertCityInDict("Norfolk", 5);
	InsertCityInDict("Raleigh", 5);
	InsertCityInDict("Atlanta", 5);
	InsertCityInDict("Savannah", 5);
	InsertCityInDict("JacksonVille", 5);
	InsertCityInDict("Tampa", 5);
	InsertCityInDict("Miami", 5);*/

	//create edges
	//region 0
	EdgeDict["Portland-Seattle"] = 3;
	EdgeDict["Billings-Seattle"] = 9;
	EdgeDict["Boise-Seattle"] = 12;
	
	EdgeDict["Portland-San Fransisco"] = 24;
	EdgeDict["Boise-Portland"] = 13;
	
	EdgeDict["Billings-Boise"] = 12;
	EdgeDict["Boise-San Fransisco"] = 23;
	EdgeDict["Boise-Salt Lake City"] = 8;
	EdgeDict["Boise-Cheyenne"] = 24;

	EdgeDict["Billings-Cheyenne"] = 9;
	EdgeDict["Billings-Fargo"] = 17;
	EdgeDict["Billings-Minneapolis"] = 18;

	EdgeDict["Cheyenne-Denver"] = 0;
	EdgeDict["Cheyenne-Omaha"] = 14;
	EdgeDict["Cheyenne-Minneapolis"] = 18;

	EdgeDict["Denver-Salt Lake City"] = 21;
	EdgeDict["Denver-Santa Fe"] = 13;
	EdgeDict["Denver-Kansas City"] = 16;

	//Region 1
	//San Fransisco
	EdgeDict["San Fransisco-Salt Lake City"] = 27;
	EdgeDict["Las Vegas-San Fransisco"] = 14;
	EdgeDict["Los Angeles-San Fransisco"] = 9;
	
	//Los Angeles
	EdgeDict["Las Vegas-Los Angeles"] = 9;
	EdgeDict["Los Angeles-San Diego"] = 3;

	//Las Vegas
	EdgeDict["Las Vegas-Phoenix"] = 15;
	EdgeDict["Las Vegas-San Diego"] = 9;
	EdgeDict["Las Vegas-Salt Lake City"] = 18;
	EdgeDict["Las Vegas-Santa Fe"] = 27;

	//San Diego
	EdgeDict["Phoenix-San Diego"] = 14;

	//Pheonix
	EdgeDict["Phoenix-Santa Fe"] = 18;

	//Salt Lake City
	EdgeDict["Salt Lake City-Santa Fe"] = 28;

	//Santa Fe
	EdgeDict["Kansas City-Santa Fe"] = 16;
	EdgeDict["Oklahoma City-Santa Fe"] = 15;
	EdgeDict["Dallas-Santa Fe"] = 16;
	EdgeDict["Houston-Santa Fe"] = 21;

	//Region 2
	//Fargo
	EdgeDict["Fargo-Minneapolis"] = 6;
	EdgeDict["Duluth-Fargo"] = 6;

	//Duluth
	EdgeDict["Detroit-Duluth"] = 15;
	EdgeDict["Chicago-Duluth"] = 12;
	EdgeDict["Duluth-Minneapolis"] = 5;

	//Minneapolis
	EdgeDict["Chicago-Minneapolis"] = 8;

	//Chicago
	EdgeDict["Chicago-Kansas City"] = 8;
	EdgeDict["Chicago-St. Louis"] = 10;
	EdgeDict["Chicago-Cincinnati"] = 7;
	EdgeDict["Chicago-Detroit"] = 7;

	//St. Louis
	EdgeDict["Kansas City-St. Louis"] = 6;
	EdgeDict["Memphis-St. Louis"] = 7;
	EdgeDict["Atlanta-St. Louis"] = 12;
	EdgeDict["Cincinnati-St. Louis"] = 12;

	//Cincinnati
	EdgeDict["Cincinnati-Knoxville"] = 6;
	EdgeDict["Cincinnati-Raleigh"] = 15;
	EdgeDict["Cincinnati-Pittsburgh"] = 7;
	EdgeDict["Cincinnati-Detroit"] = 4;

	//Knoxville
	EdgeDict["Atlanta-Knoxville"] = 5;

	//Region 3
	//Kansas city
	EdgeDict["Kansas City-Oklahoma City"] = 8;
	EdgeDict["Kansas City-Memphis"] = 12;

	//Oklahoma City
	EdgeDict["Memphis-Oklahoma City"] = 14;
	EdgeDict["Dallas-Oklahoma City"] = 3;

	//Dallas
	EdgeDict["Dallas-Memphis"] = 12;
	EdgeDict["Dallas-New Orleans"] = 12;
	EdgeDict["Dallas-Houston"] = 5;

	//Houston
	EdgeDict["Houston-New Orleans"] = 8;

	//Memphis
	EdgeDict["Birmingham-Memphis"] = 6;
	EdgeDict["Memphis-New Orleans"] = 7;

	//New Orleans
	EdgeDict["Birmingham-New Orleans"] = 11;
	EdgeDict["JacksonVille-New Orleans"] = 16;

	//Birmingham
	EdgeDict["Atlanta-Birmingham"] = 3;
	EdgeDict["Birmingham-Jacksonville"] = 9;

	//Region 4
	//Detroit
	EdgeDict["Buffalo-Detroit"] = 7;
	EdgeDict["Detroit-Pittsburgh"] = 6;

	//Buffalo
	EdgeDict["Buffalo-Pittsburgh"] = 7;
	EdgeDict["Buffalo-New York"] = 8;

	//Boston
	EdgeDict["Boston-New York"] = 3;

	//New York
	EdgeDict["New York-Philadelphia"] = 0;

	//Philadelphia
	EdgeDict["Philadelphia-Washington DC"] = 3;

	//Washington
	EdgeDict["Pittsburgh-Washington DC"] = 6;
	EdgeDict["Norfolk-Washington DC"] = 5;

	//Region 5
	//Raleigh
	EdgeDict["Norfolk-Raleigh"] = 3;
	EdgeDict["Atlanta-Raleigh"] = 7;
	EdgeDict["Raleigh-Savannah"] = 7;

	//Savannah
	EdgeDict["Atlanta-Savannah"] = 7;
	EdgeDict["Jacksonville-Savannah"] = 0;

	//Tampa
	EdgeDict["Jacksonville-Tampa"] = 4;
	EdgeDict["Miami-Tampa"] = 4;
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

std::map<char*, City*>::iterator Board::GetCityDictFirstIterator()
{
	return cityDict.begin();
}

std::map<char*, City*>::iterator Board::GetCityDictLastIterator()
{
	return cityDict.end();
}