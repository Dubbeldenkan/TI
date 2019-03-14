#include "MapTile.h"

const TupleInt MapTile::_tileSize = TupleInt(100, 86);

MapTile::MapTile()
{}

MapTile::MapTile(MapTile::TileType tileType,  std::string imagePath) :
	_tileType(tileType), GameBoardObject(TupleInt(0, 0), _tileSize, imagePath)
{}

//TODO behövs constructorn nedan?
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

TupleInt MapTile::GetTileSize()
{
	return _tileSize;
}

void MapTile::SetTilePos(int r, int t)
{
	_tilePos = (TupleInt(r, t));
}

void MapTile::AddPlanet(Planet* planet)
{
	_planets.push_back(*planet);
}