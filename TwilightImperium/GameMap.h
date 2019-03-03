#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "MapTile.h"

#include <map>
#include <math.h>
#include <utility>

class GameMap
{
private:
	std::map<TupleInt, MapTile> _map;
	const int numberOfLayers = 3;

public:
	GameMap();
	GameMap& operator=(const GameMap&);
	~GameMap();

	void CreateGameMap();

private:
	void Add2Map(int, int, TupleInt, std::string);

	double degCos(int);
	double degSin(int);
};

#endif // !GAME_MAP_H