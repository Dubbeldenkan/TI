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
	tempSystem = MapTile(MapTile::RegularSystem);
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
	TIParserNS::ListNode* currentSystem = TIParserNS::TIParser::ReadDataFile(_dataFile);
	
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
				int resourceValue = stoi(tempNode->GetData());
				tempNode->GetNext(&tempNode);
				int influenceValue = stoi(tempNode->GetData());
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

//TODO gör om så att det görs på ett snyggare sätt. använd factory?
MapTile GameMap::CreateSystem(std::string systemType)
{
	MapTile::TileType tileType = MapTile::GetSystemType(systemType);
	MapTile mapTile = MapTile(tileType);
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

TIParserNS::ListNode* GameMap::Save() const
{
	TIParserNS::ListNode* gameMapNode = new TIParserNS::ListNode("GameMap");

	TIParserNS::ListNode* currentNode = new TIParserNS::ListNode("");
	TIParserNS::ListNode* oldNode = NULL;
	
	std::map<TupleInt, MapTile>::const_iterator it;
	for (it = _map.begin(); it != _map.end(); it++)
	{
		currentNode = new TIParserNS::ListNode("MapTile");
		TIParserNS::ListNode* mapPosHead = new TIParserNS::ListNode("MapPos");
		TIParserNS::ListNode* mapPos = it->first.ToListNode();
		mapPosHead->SetChild(mapPos);

		TIParserNS::ListNode* systemType = new TIParserNS::ListNode(it->second.GetTileType());
		currentNode->SetChild(mapPosHead);
		mapPosHead->SetNext(systemType);

		if ((it->second.GetTileType() == MapTile::RegularSystem) || (it->second.GetTileType() == MapTile::HomeSystem))
		{
			const std::vector<Planet>* planets = it->second.GetPlanets();
			TIParserNS::ListNode* currentPlanetNode = new TIParserNS::ListNode(""); //TODO minnesläcka?
			TIParserNS::ListNode* oldPlanetNode = NULL;
			for (int planetCount = 0; planetCount < static_cast<int>(planets->size()); planetCount++)
			{
				currentPlanetNode = new TIParserNS::ListNode((planets->at(planetCount)).GetName());
				if (oldPlanetNode == NULL) //TODO kan man göra detta på ett snyggare sätt?
				{
					systemType->SetChild(currentPlanetNode);
				}
				else
				{
					oldPlanetNode->SetNext(currentPlanetNode);
				}
				oldPlanetNode = currentPlanetNode;
			}
		}
		if (oldNode == NULL) //TODO kan man göra detta på ett snyggare sätt?
		{
			gameMapNode->SetChild(currentNode);
		}
		else
		{
			oldNode->SetNext(currentNode);
		}
		oldNode = currentNode;
	}

	return gameMapNode;
}

void GameMap::Load(TIParserNS::ListNode* gameMapNode)
{
	//TODO fixa mecatol rex
	TIParserNS::ListNode* mapTileNode = NULL;
	gameMapNode->GetChild(&mapTileNode);

	do
	{
		TIParserNS::ListNode* mapPosNode;
		TIParserNS::ListNode* xPosNode;
		TIParserNS::ListNode* xPosValue;
		TIParserNS::ListNode* yPosNode;

		mapTileNode->GetChild(&mapPosNode);
		mapPosNode->GetChild(&xPosNode);
		xPosNode->GetChild(&xPosValue);
		int xValue = stoi(xPosValue->GetData());
		xPosNode->GetNext(&yPosNode);
		yPosNode->GetChild(&yPosNode);

		TupleInt tilePos = TupleInt(xValue, stoi(yPosNode->GetData()));
		
		TIParserNS::ListNode* tileTypeNode;
		mapPosNode->GetNext(&tileTypeNode);
		MapTile::TileType tileType = static_cast<MapTile::TileType>(stoi(tileTypeNode->GetData()));

		_map.insert(std::make_pair(tilePos, MapTile(tileType)));
		_map[tilePos].SetGraphicalPos(CalculateGraphicalPosForTile(tilePos.GetX(), tilePos.GetY()));

		TIParserNS::ListNode* planetNameNode = NULL;
		if (!tileTypeNode->GetChild(&planetNameNode))
		{
			do {
				std::string planetName = planetNameNode->GetData();
				//TODO går detta att göra på ett bättre sätt? Nu letas alla planeter igenom för varje planet. 
				TIParserNS::ListNode* currentSystem = TIParserNS::TIParser::ReadDataFile(_dataFile);
				do {
					TIParserNS::ListNode* currentPlanet;
					if (!currentSystem->GetChild(&currentPlanet))
					{
						do {
							if (planetName.compare(currentPlanet->GetData()) == 0)
							{
								TIParserNS::ListNode* planetData;
								currentPlanet->GetChild(&planetData);
								int resourceValue = stoi(planetData->GetData());
								planetData->GetNext(&planetData);
								int influenceValue = stoi(planetData->GetData());
								planetData->GetNext(&planetData);
								std::string techSpec = planetData->GetData();
								_map[tilePos].AddPlanet(&Planet(planetName, resourceValue, influenceValue, techSpec));
							}
						} while (!currentPlanet->GetNext(&currentPlanet));
					}
				} while (!currentSystem->GetNext(&currentSystem));
			} while (!planetNameNode->GetNext(&planetNameNode));
			_map[tilePos].SetPlanetsPositions();
		}
	} while (!mapTileNode->GetNext(&mapTileNode));
}

TupleInt GameMap::GetSystemFromPlanetName(std::string planetName) const
{
	std::map<TupleInt, MapTile>::const_iterator mapIt;
	TupleInt result = TupleInt(-1, -1);

	for (mapIt = _map.begin(); mapIt != _map.end(); mapIt++) //TODO lägg till exception om det är så att rätt planet inte kan hittas
	{
		const std::vector<Planet>* systemPlanets = mapIt->second.GetPlanets();
		for (int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
		{
			if (planetName.compare(mapIt->second.GetPlanet(planetCount)->GetName()) == 0)
			{
				result = mapIt->first;
				break;
			}
		}
	}
	return result;
}

const std::vector<Planet>* GameMap::GetPlanetsFromSystem(TupleInt system) const
{
	return _map.at(system).GetPlanets();
	
}

const Planet* GameMap::GetPlanetFromName(std::string planetName) const
{
	TupleInt system = GetSystemFromPlanetName(planetName);
	const std::vector<Planet>* planets = _map.at(system).GetPlanets();
	for (int planetCount = 0; planetCount < static_cast<int>(planets->size()); planetCount++)
	{
		if (planetName.compare(planets->at(planetCount).GetName()) == 0)
		{
			return &(planets->at(planetCount));
		}
	}
	return NULL;
}

void GameMap::CleanUpMap()
{
	_map.clear();
}