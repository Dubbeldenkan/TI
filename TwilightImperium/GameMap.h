#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "MapTile.h"

#include <utility>
#include <map>

class GameMap
{
private:
	std::map<TupleInt, MapTile> _map;

public:
	GameMap();
	~GameMap();

	void CreateGameMap();

private:
	void Add2Map(int, int, TupleInt, std::string);
};

#endif // !GAME_MAP_H