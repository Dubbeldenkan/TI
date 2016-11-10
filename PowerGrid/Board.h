#ifndef BOARD_H
#define BOARD_H

#include "Image.h"
#include "City.h"
#include <map>

class Board
{
	bool _usedRegions[6];
	char* _mapName;
	Image _mapImage;
	std::map<char*, City*> cityDict;
	std::map<char*, int> EdgeDict;

public:
	Board(bool, bool, bool, bool, bool, bool, char*);
	~Board() {};

	void SetMapImage(Image);
	Image* GetMapImage();
	char* GetMapName();
	std::map<char*, City*>::iterator GetCityDictFirstIterator();
	std::map<char*, City*>::iterator GetCityDictLastIterator();

private:
	void InitMap();
	void InsertCityInDict(char*, int, int, int);
};

#endif // !BOARD_H