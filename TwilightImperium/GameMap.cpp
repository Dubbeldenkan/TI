#include "GameMap.h"

GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::CreateGameMap()
{
	// mitten
	Add2Map(0, 0, TupleInt(200, 200), "Map/MecatolRex.png");
	
	// första varvet
	Add2Map(1, 0, TupleInt(200, 150), "Map/MecatolRex.png");
	Add2Map(1, 1, TupleInt(165, 175), "Map/MecatolRex.png");
	Add2Map(1, 2, TupleInt(165, 225), "Map/MecatolRex.png");
	Add2Map(1, 3, TupleInt(200, 250), "Map/MecatolRex.png");
	Add2Map(1, 4, TupleInt(235, 225), "Map/MecatolRex.png");
	Add2Map(1, 5, TupleInt(235, 175), "Map/MecatolRex.png");

	// andra varvet
	/*Add2Map(2, 0, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 1, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 2, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 3, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 4, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 5, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 6, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 7, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 8, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 9, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 10, TupleInt(200, 200), "Map/test.png");
	Add2Map(2, 11, TupleInt(200, 200), "Map/test.png");

	// tredje varvet
	Add2Map(3, 0, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 1, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 2, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 3, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 4, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 5, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 6, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 7, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 8, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 9, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 10, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 11, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 12, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 13, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 14, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 15, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 16, TupleInt(200, 200), "Map/test.png");
	Add2Map(3, 17, TupleInt(200, 200), "Map/test.png");*/
}

void GameMap::Add2Map(int r, int t, TupleInt tupleInt, std::string path)
{
	_map.insert(std::make_pair(TupleInt(r, t), MapTile(tupleInt, path)));
}