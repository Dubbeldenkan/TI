#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "GameBoardObject.h"
#include "HelpStructs.h"

class MapTile : GameBoardObject
{
public:

private:
	const TupleInt _tileSize = TupleInt(40, 40);

public:
	MapTile(TupleInt, std::string);
	~MapTile();

private:
	TupleInt _tilePos;

};

#endif // !MAP_TILE_H