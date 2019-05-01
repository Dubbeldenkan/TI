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

	CreateAndAddMecatolRex();

	for (int r = 1; r <= _numberOfLayers; r++)
	{
		int t = 0;
		while (t < _fullTurn)
		{
			Add2Map(r, t);
			if (r == 0)
			{
				break;
			}
			else
			{
				t += _fullTurn/(6 * r);
			}
		}
	}
	_allSystemVector.clear();
}

void GameMap::CreateAndAddMecatolRex()
{
	MapTile tempSystem;
	tempSystem = MapTile(MapTile::RegularSystem, "Map/RegularSystem.png");
	std::string planetName = "Mecatol Rex";
	int resourceValue = 1;
	int influenceValue = 6;
	std::string techSpec = "None";
	tempSystem.SetGraphicalPos(CalculateGraphicalPosForTile(0, 0));

	tempSystem.AddPlanet(&Planet(planetName, resourceValue, influenceValue, techSpec));
	tempSystem.SetPlanetsPositions();
	tempSystem.SetTilePos(0, 0);
	_map.insert(std::make_pair(TupleInt(0, 0), tempSystem));
}

void GameMap::CreateAllSystems()
{
	//TODO gör så att det finns olika planetbilder
	TIParserNS::ListNode* currentSystem = TIParserNS::TIParser::ReadFile(_dataFile);
	
	do
	{
		MapTile tempSystem = CreateSystem(currentSystem->GetData());
		TIParserNS::ListNode* currentPlanet = NULL;
		if (!currentSystem->GetChild(&currentPlanet))
		{
			do
			{
				std::string planetName = currentPlanet->GetData();
				TIParserNS::ListNode* tempNode = NULL;
				currentPlanet->GetChild(&tempNode);
				int resourceValue = atoi(tempNode->GetData().c_str());
				tempNode->GetNext(&tempNode);
				int influenceValue = atoi(tempNode->GetData().c_str());
				tempNode->GetNext(&tempNode);
				std::string techSpec = tempNode->GetData().c_str();

				tempSystem.AddPlanet(&Planet(planetName, resourceValue, influenceValue, techSpec));
			} while (!currentPlanet->GetNext(&currentPlanet));
		}
		if (currentSystem->GetData().compare("RegularSystem") == 0 || currentSystem->GetData().compare("AstroidSystem") == 0 ||
			currentSystem->GetData().compare("NebulaSystem") == 0 || currentSystem->GetData().compare("SupernovaSystem") == 0)
		{
			_allSystemVector.push_back(tempSystem);
		}
		else if (currentSystem->GetData().compare("HomeSystem") == 0)
		{
			_homeSystemVector.push_back(tempSystem);
		}
		else
		{
			OutputDebugString(std::string("Error in system type").c_str());
		}
	} while (!currentSystem->GetNext(&currentSystem));
}

MapTile GameMap::CreateSystem(std::string systemType)
{
	MapTile mapTile;
	if (systemType.compare("RegularSystem") == 0)
	{
		mapTile = MapTile(MapTile::RegularSystem, "Map/RegularSystem.png");
	}
	else if (systemType.compare("HomeSystem") == 0)
	{
		mapTile = MapTile(MapTile::RegularSystem, "Map/HomeSystem.png");
	}
	else if (systemType.compare("AstroidSystem") == 0)
	{
		mapTile = MapTile(MapTile::AstroidSystem, "Map/AstroidSystem.png");
	}
	else if (systemType.compare("SupernovaSystem") == 0)
	{
		mapTile = MapTile(MapTile::SupernovaSystem, "Map/SupernovaSystem.png");
	}
	else if (systemType.compare("NebulaSystem") == 0)
	{
		mapTile = MapTile(MapTile::NebulaSystem, "Map/NebulaSystem.png");
	}
	else
	{
		OutputDebugString(std::string("Failing to read planet file").c_str());
	}
	return mapTile;
}

void GameMap::Add2Map(int r, int t)
{
	MapTile localMapTile;
	if ((r == _numberOfLayers) && ((t % 60) == 0))
	{
		int vectorLen = _homeSystemVector.size();
		int selectedSystem;
		selectedSystem = rand() % vectorLen;
		localMapTile = _homeSystemVector[selectedSystem];
		_homeSystemVector.erase(_homeSystemVector.begin() + selectedSystem);
	}
	else
	{
		int vectorLen = _allSystemVector.size();
		int selectedSystem;
		//TODO lägg in så att man inte får två specialSystem bredvid varandra. 
		selectedSystem = rand() % vectorLen;
		localMapTile = _allSystemVector[selectedSystem];
		_allSystemVector.erase(_allSystemVector.begin() + selectedSystem);
	}
	localMapTile.SetGraphicalPos(CalculateGraphicalPosForTile(r, t));
	localMapTile.SetTilePos(r, t);
	localMapTile.SetPlanetsPositions();
	_map.insert(std::make_pair(TupleInt(r, t), localMapTile));
}

std::vector<MapTile*> GameMap::GetNeighbourSystems(TupleInt SystemPosition)
{
	int r = SystemPosition.GetX();
	int t = SystemPosition.GetY();
	std::vector<MapTile*> neighbourVector;
	bool foundAllNeighbours = false;

	if (r > 0)
	{
		if (r == 1)
		{
			neighbourVector.push_back(&_map.find(TupleInt(0, 0))->second);
		}
		else if (_map.find(TupleInt(r - 1, t)) != _map.end())
		{
			neighbourVector.push_back(&_map.find(TupleInt(r - 1, t))->second);
		}
		else
		{
			int angleDiff = 0;
			while (_map.find(TupleInt(r - 1, (t + angleDiff) % _fullTurn)) == _map.end())
			{
				angleDiff -= 10;
			}
			neighbourVector.push_back(&_map.find(TupleInt(r - 1, t + angleDiff))->second);
			angleDiff = 0;
			while (_map.find(TupleInt(r - 1, (t + angleDiff) % _fullTurn)) == _map.end())
			{
				angleDiff += 10;
			}
			neighbourVector.push_back(&_map.find(TupleInt(r - 1, (t + angleDiff) % _fullTurn))->second);
		}

		neighbourVector.push_back(&_map.find(TupleInt(r, (t - _layerDegree[r]) % _fullTurn))->second);
		neighbourVector.push_back(&_map.find(TupleInt(r, (t + _layerDegree[r]) % _fullTurn))->second);

		if (r < _numberOfLayers)
		{
			if (_map.find(TupleInt(r + 1, t)) != _map.end())
			{
				neighbourVector.push_back(&_map.find(TupleInt(r + 1, (t - _layerDegree[r + 1]) % _fullTurn))->second);
				neighbourVector.push_back(&_map.find(TupleInt(r + 1, t))->second);
				neighbourVector.push_back(&_map.find(TupleInt(r + 1, (t + _layerDegree[r + 1]) % _fullTurn))->second);
			}
			else
			{
				neighbourVector.push_back(&_map.find(TupleInt(r + 1, (t + _layerDegree[r + 1] / 2)  % _fullTurn))->second);
				neighbourVector.push_back(&_map.find(TupleInt(r + 1, (t - _layerDegree[r + 1] / 2) % _fullTurn))->second);
			}
		}
	}
	else
	{
		for (int tIndex = 0; tIndex < _fullTurn; tIndex += _layerDegree[r + 1])
		{
			neighbourVector.push_back(&_map.find(TupleInt(1, tIndex))->second);
		}
	}
	
	return neighbourVector;
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
	return -cos(rad);
}

double GameMap::degSin(int deg)
{
	double rad = PI * double(deg) / 180.0;
	return sin(rad);
}

TupleInt GameMap::CalculateGraphicalPosForTile(TupleInt mapPos)
{
	return CalculateGraphicalPosForTile(mapPos.GetX(), mapPos.GetY());
}

TupleInt GameMap::CalculateGraphicalPosForTile(int r, int t)
{
	TupleInt tileSize = MapTile::GetTileSize();
	//gör detta till en const istället eftersom att den inte ändras
	TupleInt middleTilePos = TupleInt(tileSize.GetX()*_numberOfLayers + GameBoardObject::GetGameMapPos().GetX(),
		tileSize.GetY()*_numberOfLayers + GameBoardObject::GetGameMapPos().GetY());

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
	return TupleInt(xPos, yPos);
}

const std::map<TupleInt, MapTile>* GameMap::GetMap() const
{
	return &_map;
}