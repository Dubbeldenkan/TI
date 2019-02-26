#include "MapTile.h"

const TupleInt MapTile::_tileSize = TupleInt(50, 50);

MapTile::MapTile()
{}

MapTile::MapTile(TupleInt graphicalPos, std::string imagePath) :
	GameBoardObject(graphicalPos, _tileSize, imagePath)
{}

MapTile::MapTile(const MapTile &mapTile) : 
	GameBoardObject(mapTile._graphicalPos, mapTile._image)
{
	_tilePos = mapTile._tilePos;
}

MapTile& MapTile::operator=(const MapTile& mapTile)
{
	_tilePos = mapTile._tilePos;
	_graphicalPos = mapTile._graphicalPos;
	_image = mapTile._image;
	return *this;
}

MapTile::~MapTile()
{}