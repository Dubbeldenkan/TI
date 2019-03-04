#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "GameBoardObject.h"
#include "HelpStructs.h"
#include "Planet.h"

class MapTile : public GameBoardObject
{
public:
	enum TileType {RegularSystem, HomeSystem, AstroidSystem, NebulaSystem, SupernovaSystem};

private:
	static const TupleInt _tileSize;
	TupleInt _tilePos;

protected:
	std::vector<Planet> _planets;

public:
	MapTile();
	MapTile(std::string);
	MapTile(TupleInt, std::string);
	
	MapTile& operator=(const MapTile&);
	MapTile(MapTile const&);
	~MapTile();

	static TupleInt GetTileSize();

private:

};

#endif // !MAP_TILE_H