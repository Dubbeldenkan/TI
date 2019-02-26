#include "GameMap.h"

GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::CreateGameMap()
{
	Add2Map(0, 0, TupleInt(200, 200), "Map/test.png");
}

void GameMap::Add2Map(int r, int t, TupleInt tupleInt, std::string path)
{
	_map.insert(std::make_pair(TupleInt(r, t), MapTile(tupleInt, path)));
}