#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "MapTile.h"
#include "TIParser.h"

#include <map>
#include <math.h>
#include <utility>
#include <vector>

class GameMap
{
private:
	std::map<TupleInt, MapTile> _map;
	std::vector<MapTile> _allSystemVector;
	std::vector<MapTile> _homeSystemVector;
	const int _numberOfLayers = 3;
	const int _numberOfRandomSystemsToRemove = 2;
	const int _numberOfRegularSystems = 39;
	const int _numberOfAstroidSystems = 2;
	const int _layerDegree[4] = { 360, 60, 30, 20 };
	const int _fullTurn = 360;
	const std::string _dataFile = "Planets.txt";

public:
	GameMap();
	GameMap& operator=(const GameMap&);
	~GameMap();

	void CreateGameMap();
	std::vector<MapTile*> GetNeighbourSystems(TupleInt);

private:
	void CreateAllSystems();
	MapTile CreateSystem(std::string);
	MapTile CreateSystem(MapTile::TileType);
	void Add2Map(int, int);
	void RemoveRandomTiles();

	double degCos(int);
	double degSin(int);
};

#endif // !GAME_MAP_H