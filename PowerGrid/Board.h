#ifndef BOARD_H
#define BOARD_H

#include "Image.h"
#include "City.h"
#include <map>
#include <vector>
#include <string>

class Board
{
	std::vector<int> _usedRegions;
	char* _mapName;
	Image _mapImage;
	std::map<char*, City*> _cityDict;
	std::map<std::string, int> _edgeDict;

public:
	Board();
	Board(std::vector<int>, char*);
	~Board() {};

	void SetMapImage(Image);
	Image* GetMapImage();
	char* GetMapName();
	//TODO behövs dessa här under?
	std::map<char*, City*>::iterator GetCityDictFirstIterator();
	std::map<char*, City*>::iterator GetCityDictLastIterator();
	std::vector<int> GetRegionsInPlay();
	bool CityIsInUsedRegion(City*);
	City* GetCityFromName(char*);
	int GetRoadCost(std::vector<City*>, char*);

private:
	void InitMap();
	void InsertCityInDict(char*, int, int, int);
	int GetCostBetweenTwoCities(char*, char*);
	std::vector<City*> GetNeighbourCities(City*);
};

#endif // !BOARD_H