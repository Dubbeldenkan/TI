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
	TupleInt tileSize = MapTile::GetTileSize();
	int wholeCircle = 360; // using degree instead of radiants so that double is not needed
	TupleInt middleTilePos = TupleInt(tileSize.GetX()*numberOfLayers + GameBoardObject::GetMapPos().GetX(),
		tileSize.GetY()*numberOfLayers + GameBoardObject::GetMapPos().GetY());

	for (int r = 0; r <= numberOfLayers; r++)
	{
		int t = 0;
		while (t < wholeCircle)
		{
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
				int temp = distance * tileSize.GetY()*degSin(straightAngle - 120);
				xPos = middleTilePos.GetX() + int(r*tileSize.GetY()*degSin(straightAngle) + 
					distance*tileSize.GetY()*degSin(straightAngle - 120));
				yPos = middleTilePos.GetY() + int(r*tileSize.GetY()*degCos(straightAngle) + 
					distance * tileSize.GetY()*degCos(straightAngle - 120));
			}
			Add2Map(r, t, TupleInt(xPos, yPos), "Map/EmptyTile.png");
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
}

void GameMap::Add2Map(int r, int t, TupleInt graphicalPos, std::string path)
{
	_map.insert(std::make_pair(TupleInt(r, t), MapTile(graphicalPos, path)));
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