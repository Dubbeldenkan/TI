#include "MapTile.h"

const TupleInt MapTile::_tileSize = TupleInt(100, 86);

MapTile::MapTile()
{}

MapTile::MapTile(MapTile::TileType tileType,  std::string imagePath) :
	_tileType(tileType), GameBoardObject(TupleInt(0, 0), _tileSize, imagePath)
{}

MapTile::MapTile(const MapTile &mapTile) : 
	GameBoardObject(mapTile._graphicalPos, mapTile._image)
{
	CopyMapTile(mapTile);
}

MapTile& MapTile::operator=(const MapTile& mapTile)
{
	CopyMapTile(mapTile);
	return *this;
}

void MapTile::CopyMapTile(const MapTile& mapTile)
{
	_tilePos = mapTile._tilePos;
	_tileType = mapTile._tileType;
	_graphicalPos = mapTile._graphicalPos;
	_image = mapTile._image;
	_planets = mapTile._planets;
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

void MapTile::SetPlanetsPositions()
{
	int numberOfPlanets = _planets.size();
	switch (numberOfPlanets)
	{
	case 1:
	{
		TupleInt planetPos = _graphicalPos + _tileSize.Division(2) - Planet::_imageSize.Division(2);
		_planets[0].SetGraphicalPos(planetPos);
		break;
	}
	case 2:
	{
		//TODO randomize var planeterna hamnar
		TupleInt planetPos = _graphicalPos + _tileSize.Division(numberOfPlanets) -
			Planet::_imageSize.Division(1.3);
		for (int planetCount = 0; planetCount < numberOfPlanets; planetCount++)
		{
			_planets[planetCount].SetGraphicalPos(planetPos + _tileSize.Division(3.5)*((double) planetCount));
			_planets[planetCount].SetImageScale(static_cast<float>(1.0/1.2));
		}
		break;
	}
	case 3:
	{
		//TODO randomize var planeterna hamnar
		TupleInt planetPos = _graphicalPos + _tileSize.Division(numberOfPlanets) -
			Planet::_imageSize.Division(numberOfPlanets);
		_planets[0].SetGraphicalPos(planetPos);
		_planets[1].SetGraphicalPos(planetPos + TupleInt(_tileSize.GetX()/3, 0));
		_planets[2].SetGraphicalPos(planetPos + TupleInt(_tileSize.GetX()/5, _tileSize.GetY()/3));
		for (int planetCount = 0; planetCount < numberOfPlanets; planetCount++)
		{
			_planets[planetCount].SetImageScale(static_cast<float>(1.0/1.5));
		}
		break;
	}
	default:
		break;
	}

}

const std::vector<Planet>* MapTile::GetPlanets() const
{
	return &_planets;
}

const Planet* MapTile::GetPlanet(int planetCount) const
{
	return &_planets[planetCount];
}

void MapTile::Action(GameBoardObject *)
{
	_selectedObject = this;
}


bool MapTile::isMapTile() {
	return true;
}