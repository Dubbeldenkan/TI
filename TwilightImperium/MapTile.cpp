#include "MapTile.h"

MapTile::MapTile(TupleInt graphicalPos, std::string imagePath) :
	GameBoardObject(graphicalPos, _tileSize, imagePath)
{
	
}

MapTile::~MapTile()
{}