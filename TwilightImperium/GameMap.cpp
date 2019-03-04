#include "GameMap.h"

#define PI 3.14159265

GameMap::GameMap()
{
}

GameMap& GameMap::operator=(const GameMap& gameMap)
{
	_map = gameMap._map;
	return *this;
}


GameMap::~GameMap()
{
}

void GameMap::CreateGameMap()
{
	CreateAllSystems();
	RemoveRandomTiles();

	int wholeCircle = 360; // using degree instead of radiants so that double is not needed

	for (int r = 0; r <= _numberOfLayers; r++)
	{
		int t = 0;
		while (t < wholeCircle)
		{
			Add2Map(r, t);
			if (r == 0)
			{
				break;
			}
			else
			{
				t += 360/(6 * r);
			}
		}
	}
	_allSystemVector.clear();
}


void GameMap::CreateAllSystems()
{
	for (int i = 0; i < 39; i++)// _numberOfRegularSystems; i++) //TODO ändra tillbaka
	{
		_allSystemVector.push_back(CreateSystem(MapTile::RegularSystem));
	}
	/*for (int i = 0; i < _numberOfAstroidSystems; i++)
	{
		_allSystemVector.push_back(CreateSystem(MapTile::AstroidSystem));
	}
	_allSystemVector.push_back(CreateSystem(MapTile::NebulaSystem));*/
	_allSystemVector.push_back(CreateSystem(MapTile::SupernovaSystem));
}

MapTile GameMap::CreateSystem(MapTile::TileType tileType)
{
	MapTile mapTile;
	switch (tileType)
	{
	case MapTile::RegularSystem:
		mapTile = MapTile("Map/RegularSystem.png");
		break;
	case MapTile::HomeSystem:
		mapTile = MapTile("Map/HomeSystem.png");
		break;
	case MapTile::AstroidSystem:
		mapTile = MapTile("Map/AstroidSystem.png");
		break;
	case MapTile::NebulaSystem:
		mapTile = MapTile("Map/NebulaSystem.png");
		break;
	case MapTile::SupernovaSystem:
		mapTile = MapTile("Map/SupernovaSystem.png");
		break;
	default:
		break;
	}
	return mapTile;
}

void GameMap::Add2Map(int r, int t)
{
	TupleInt tileSize = MapTile::GetTileSize();
	TupleInt middleTilePos = TupleInt(tileSize.GetX()*_numberOfLayers + GameBoardObject::GetMapPos().GetX(),
		tileSize.GetY()*_numberOfLayers + GameBoardObject::GetMapPos().GetY());

	int xPos;
	int yPos;
	if (t % 60 == 0)
	{
		xPos = middleTilePos.GetX() + int(r*tileSize.GetY()*degSin(t));
		yPos = middleTilePos.GetY() + int(r*tileSize.GetY()*degCos(t));
	}
	else
	{
		int straightAngle = t - t % 60;
		int distance;
		if (t % 60 > 30)
		{
			distance = 2;
		}
		else
		{
			distance = 1;
		}
		xPos = middleTilePos.GetX() + int(r*tileSize.GetY()*degSin(straightAngle) +
			distance * tileSize.GetY()*degSin(straightAngle - 120));
		yPos = middleTilePos.GetY() + int(r*tileSize.GetY()*degCos(straightAngle) +
			distance * tileSize.GetY()*degCos(straightAngle - 120));
	}
	MapTile localMapTile;
	if (r == 0 && t == 0)
	{
		localMapTile = CreateSystem(MapTile::RegularSystem);
	}
	else
	{
		int vectorLen = _allSystemVector.size();
		int selectedSystem = rand() % vectorLen;
		localMapTile = _allSystemVector[selectedSystem];
		_allSystemVector.erase(_allSystemVector.begin() + selectedSystem);
	}
	localMapTile.SetGraphicalPos(TupleInt(xPos, yPos));
	_map.insert(std::make_pair(TupleInt(r, t), localMapTile));
}

void GameMap::RemoveRandomTiles()
{
	for (int i = 0; i < _numberOfRandomSystemsToRemove; i++)
	{
		int vectorLen = _allSystemVector.size();
		int system2Remove = rand() % vectorLen;
		_allSystemVector.erase(_allSystemVector.begin() + system2Remove);
	}
}

double GameMap::degCos(int deg)
{
	double rad = PI * double(deg) / 180.0;
	return cos(rad);
}

double GameMap::degSin(int deg)
{
	double rad = PI * double(deg) / 180.0;
	return sin(rad);
}