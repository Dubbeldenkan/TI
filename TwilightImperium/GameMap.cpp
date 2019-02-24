#include "GameMap.h"

#include <utility>

GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::CreateGameMap()
{
	MapTile test = MapTile(TupleInt(200, 200), "Map/test.png");
	//_map[TupleInt(0, 0)] = test;

	std::map<std::pair<int, int>, int> testMap;
	testMap[std::make_pair(0, 0)] = 1;
}