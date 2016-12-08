#ifndef BOARD_H
#define BOARD_H

#include "Image.h"
#include "City.h"
#include <map>
#include <vector>
#include <string>

class Board
{
public:
	struct GetRoadCostOutput
	{
		int cost;
		std::string cityList;
	};

private:
	std::vector<int> _usedRegions;
	char* _mapName;
	Image _mapImage;
	std::map<std::string, City*> _cityDict;
	std::map<std::string, int> _edgeDict;
	const int numberOfCitiesInEachRegion = 7;

public:
	Board();
	Board(std::vector<int>, char*);
	Board& operator=(const Board&);
	~Board() {};

	void SetMapImage(Image);
	Image* GetMapImage();
	char* GetMapName();
	std::map<std::string, City*>::iterator GetCityDictFirstIterator();
	std::map<std::string, City*>::iterator GetCityDictLastIterator();
	std::vector<int> GetRegionsInPlay();
	bool CityIsInUsedRegion(City*);
	City* GetCityFromName(char*);
	GetRoadCostOutput GetRoadCost(std::vector<City*>, char*);
	City* GetRandomCity(int);
	int GetCostBetweenTwoCities(char*, char*);
	std::vector<City*> GetNeighbourCities(City*);
	void ResetBoard();

private:
	void InitMap();
	void InsertCityInDict(char*, int, int, int);
};

#endif // !BOARD_H