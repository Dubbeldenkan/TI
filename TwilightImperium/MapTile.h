#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "GameBoardObject.h"
#include "HelpStructs.h"

class MapTile : GameBoardObject
{
public:

private:
	static const TupleInt _tileSize;
	TupleInt _tilePos;

public:
	MapTile();
	MapTile(TupleInt, std::string);
	
	MapTile& operator=(const MapTile&);
	MapTile(MapTile const&);
	~MapTile();

private:

};

#endif // !MAP_TILE_H