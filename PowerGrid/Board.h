#ifndef BOARD_H
#define BOARD_H

#include "Image.h"
#include "City.h"
#include <map>
#include <vector>

class Board
{
	std::vector<int> _usedRegions;
	char* _mapName;
	Image _mapImage;
	std::map<char*, City*> cityDict;
	std::map<char*, int> EdgeDict;

public:
	Board();
	Board(std::vector<int>, char*);
	~Board() {};

	void SetMapImage(Image);
	Image* GetMapImage();
	char* GetMapName();
	std::map<char*, City*>::iterator GetCityDictFirstIterator();
	std::map<char*, City*>::iterator GetCityDictLastIterator();
	std::vector<int> GetRegionsInPlay();

private:
	void InitMap();
	void InsertCityInDict(char*, int, int, int);
};

#endif // !BOARD_H