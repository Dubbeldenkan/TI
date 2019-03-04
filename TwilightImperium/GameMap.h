#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "MapTile.h"

#include <map>
#include <math.h>
#include <utility>
#include <vector>

class GameMap
{
private:
	std::map<TupleInt, MapTile> _map;
	std::vector<MapTile> _allSystemVector;
	const int _numberOfLayers = 3;
	const int _numberOfRandomSystemsToRemove = 2;
	const int _numberOfRegularSystems = 29;
	const int _numberOfAstroidSystems = 2;

public:
	GameMap();
	GameMap& operator=(const GameMap&);
	~GameMap();

	void CreateGameMap();

private:
	void CreateAllSystems();
	MapTile CreateSystem(MapTile::TileType);
	void Add2Map(int, int);
	void RemoveRandomTiles();

	double degCos(int);
	double degSin(int);
};

#endif // !GAME_MAP_H