#include "Player.h"

const std::string Player::_shipIndicatorPath = "Unit/ShipIndicator.png";
const TupleInt Player::_playerMetricFirstPos = TupleInt(40, 90);
const TupleInt Player::_playerMetricDiffPos = TupleInt(65, 0);
const TupleInt Player::_commandCounterMetricPos = TupleInt(290, 25);

PlanetContainer::PlanetContainer(const Planet* planet)
{
	_planet = planet;
}

const Planet* PlanetContainer::GetPlanet() const
{
	return _planet;
}

void PlanetContainer::SetToExhausted()
{
	_exhausted = true;
}

void PlanetContainer::UnsetExhausted()
{
	_exhausted = false;
}

Player::Player(Race::RaceEnum raceType, GraphicsNS::Graphics::Color color, const GameMap* gameMap, int playerGraphicalPos) :
	GameBoardObject()
{
	_color = color;
	_race = Race::CreateRace(raceType);
	
	TIParserNS::ListNode* raceData = TIParserNS::TIParser::ReadDataFile(_race.GetDataFilePath());
	raceData->GetChild(&raceData);
	SetStartPlanets(raceData, gameMap);
	raceData->GetNext(&raceData);
	SetPlayerImage(raceData);
	raceData->GetNext(&raceData);
	SetStartUnits(raceData);

	_shipIndicator = _g->LoadImageFromFile(_shipIndicatorPath, _shipIndicatorSize, _shipIndicatorSize);

	_posInPlayerOrder = playerGraphicalPos;
	_graphicalPos = TupleInt(_playerSheetPos.GetX(), _playerSheetPos.GetY() + (_playerSheetSize.GetY()*_posInPlayerOrder));
}

Player::Player(TIParserNS::ListNode* playerToLoad, const GameMap* gameMap) :
	GameBoardObject()
{
	_race = Race(playerToLoad->GetData());
	_shipIndicator = _g->LoadImageFromFile(_shipIndicatorPath, _shipIndicatorSize, _shipIndicatorSize);
	SetImage(_playerSheetPath, _playerSheetSize);

	playerToLoad->GetChild(&playerToLoad);
	TIParserNS::ListNode* valueNode = NULL;
	do {
		if (playerToLoad->GetData().compare("playerOrder") == 0) //TODO borde man göra detta mer generiskt för att inte råka ha stavfel?
		{
			playerToLoad->GetChild(&valueNode);
			_posInPlayerOrder = stoi(valueNode->GetData());
		}
		else if (playerToLoad->GetData().compare("color") == 0)
		{
			playerToLoad->GetChild(&valueNode);
			_color = static_cast<GraphicsNS::Graphics::Color>(stoi(valueNode->GetData()));
		}
		else if (playerToLoad->GetData().compare("homeSystem") == 0)
		{
			playerToLoad->GetChild(&valueNode);
			_homeSystem = TupleInt(valueNode);
		}
		else if (playerToLoad->GetData().compare("Planets") == 0)
		{
			TIParserNS::ListNode* planet = NULL;
			playerToLoad->GetChild(&planet);
			do {
				std::string planetName = planet->GetData();
				_planets.insert(std::make_pair(planetName, PlanetContainer(gameMap->GetPlanetFromName(planetName))));
			} while (!planet->GetNext(&planet));
		}
		else if (playerToLoad->GetData().compare("UnitMap") == 0)
		{

			TIParserNS::ListNode* unitMapEntity = NULL;
			playerToLoad->GetChild(&unitMapEntity);
			do
			{
				TIParserNS::ListNode* unitStackNode = NULL;
				TIParserNS::ListNode* systemNode = NULL;

				unitMapEntity->GetChild(&valueNode);
				valueNode->GetChild(&systemNode);
				TupleInt system = TupleInt(systemNode);
				valueNode->GetNext(&unitStackNode);
				_unitMap[system] = UnitStack(unitStackNode);

			} while (!unitMapEntity->GetNext(&unitMapEntity));
		}
	} while (!playerToLoad->GetNext(&playerToLoad));

	_graphicalPos = TupleInt(_playerSheetPos.GetX(), _playerSheetPos.GetY() + (_playerSheetSize.GetY()*_posInPlayerOrder));
}

Player& Player::operator=(const Player& player)
{
	CopyPlayer(player);
	return *this;
}

Player::Player(const Player &player) :
	GameBoardObject(player._graphicalPos, player._image, _layerValue)
{
	CopyPlayer(player);
}

void Player::CopyPlayer(const Player& player)
{
	_unitMap = player._unitMap;
	_color = player._color;
	_race = player._race;
	_planets = player._planets;
	_shipIndicator = player._shipIndicator;
	_posInPlayerOrder = player._posInPlayerOrder;
	_image = player._image;
	_graphicalPos = player._graphicalPos;
	_homeSystem = player._homeSystem;
}

Player::~Player()
{}

void Player::SetStartPlanets(TIParserNS::ListNode* startPlanets, const GameMap* gameMap)
{
	TIParserNS::ListNode* planet = NULL;
	startPlanets->GetChild(&planet);
	std::string planetName = planet->GetData();
	_homeSystem = gameMap->GetSystemFromPlanetName(planetName);

	const std::vector<Planet>* systemPlanets = gameMap->GetPlanetsFromSystem(_homeSystem);
	for (int planetCount = 0; planetCount < static_cast<int>(systemPlanets->size()); planetCount++)
	{
		const Planet* planet = &(systemPlanets->at(planetCount));
		_planets.insert(std::make_pair(planet->GetName(), PlanetContainer(planet)));
	}
}

void Player::SetPlayerImage(TIParserNS::ListNode* listNode)
{
	listNode->GetChild(&listNode);
	SetImage(listNode->GetData(), _playerSheetSize);
}

void Player::SetStartUnits(TIParserNS::ListNode* listNode)
{
	listNode->GetChild(&listNode);
	_unitMap.insert(std::pair<TupleInt, UnitStack>(_homeSystem, UnitStack()));
	do
	{
		std::string unitName = listNode->GetData();
		TIParserNS::ListNode* tempNode = NULL;
		listNode->GetChild(&tempNode);
		int numberOfUnits = atoi(tempNode->GetData().c_str());

		_unitMap[_homeSystem].AddUnits(unitName, numberOfUnits);
	} while (!listNode->GetNext(&listNode));
}

void Player::DrawObject()
{
	DrawPlanetMarkers();
	DrawUnits();
	DrawPlayerSheet();
	if (_playerHasPassed)
	{
		_g->DrawRectangle(_passButtonPos.GetX(), _passButtonPos.GetY() + _posInPlayerOrder*_playerSheetSize.GetY(), 
			PassButton::_imageSize.GetX(), PassButton::_imageSize.GetY(), _color);
		_g->PrintText15("Passed", _passButtonPos.GetX(), _passButtonPos.GetY() + _posInPlayerOrder * _playerSheetSize.GetY(),
			GraphicsNS::Graphics::BLACK);
	}
}

void Player::DrawPlanetMarkers()
{
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		TupleInt planetPos = it->second.GetPlanet()->GetGraphicalPos();
		_g->DrawRectangle(planetPos.GetX(), planetPos.GetY(),
			_planetIndicatorSize, _planetIndicatorSize, _color);
	}
}

void Player::DrawUnits()
{
	std::map<TupleInt, UnitStack>::iterator it;
	for (it = _unitMap.begin(); it != _unitMap.end(); it++)
	{
		int numberOfShips = it->second.GetSum();
		if (0 < numberOfShips)
		{
			TupleInt graphicalPos = GameMap::CalculateGraphicalPosForTile(it->first) + _unitPosInTile;
			_g->DrawWithColor(_shipIndicator, graphicalPos.GetX(), graphicalPos.GetY(), _color);
			_g->PrintText15(numberOfShips, graphicalPos.GetX() + _shipIndicator->GetXSize(), graphicalPos.GetY(), _color);
		}
	}
}

void Player::DrawPlayerSheet()
{
	_g->Draw(_image, _graphicalPos.GetX(), _graphicalPos.GetY(), _scale);
	_g->PrintText15(_race.GetRaceName(), _graphicalPos.GetX(), _graphicalPos.GetY(), _color);
	_g->PrintText15(_commandPool, _graphicalPos.GetX() + _commandCounterMetricPos.GetX(),
		_graphicalPos.GetY() + _commandCounterMetricPos.GetY(), _color);

	TupleInt playerMetricGraphPos = TupleInt(_graphicalPos.GetX() + _playerMetricFirstPos.GetX(), 
		_graphicalPos.GetY() + _playerMetricFirstPos.GetY());
	_g->PrintText15(_tradeGoods, playerMetricGraphPos.GetX(), playerMetricGraphPos.GetY(), _color);
	_g->PrintText15(_resources, playerMetricGraphPos.GetX() + _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), _color);
	_g->PrintText15(_influence, playerMetricGraphPos.GetX() + 2*_playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), _color);
	_g->PrintText15(_strategyAllocation, playerMetricGraphPos.GetX() + 3 * _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), _color);
	_g->PrintText15(_fleetSupply, playerMetricGraphPos.GetX() + 4 * _playerMetricDiffPos.GetX(), playerMetricGraphPos.GetY(), _color);
}

void Player::PrepareForGameRound()
{
	ResetPlanets();
	_resources = CalculateResources();
	_influence = CalculateInfluence();
	_playerHasPassed = false;
}

void Player::ResetPlanets()
{
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		it->second.UnsetExhausted();
	}
}

int Player::CalculateResources()
{
	int resources = 0;
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		resources += it->second.GetPlanet()->GetResources();
	}
	return resources;
}

int Player::CalculateInfluence()
{
	int influence = 0;
	std::map<std::string, PlanetContainer>::iterator it;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		influence += it->second.GetPlanet()->GetInfluence();
	}
	return influence;
}

bool Player::TurnIsFinished() const
{
	bool playerIsFinished = false;
	if (_playerHasPassed) // TODO Fixa så att man inte kan göra detta under en pågående omgång
	{
		playerIsFinished = true;
	}
	return playerIsFinished;
}

int Player::GetPosInPlayerOrder() const
{
	return _posInPlayerOrder;
}

bool Player::GetPlayerHasPassed() const
{
	return _playerHasPassed;
}

Player::ActionState Player::GetActionState() const
{
	return _actionState;
}

Player::SubActionState Player::GetSubActionState() const
{
	return _subActionState;
}

bool Player::Action(GameBoardObject* gbo, TupleInt clickedPos)
{
	bool actionTaken = false;
	switch (_actionState)
	{
	case Player::START_ACTION:
		actionTaken = StartAction(gbo);
		break;
	case Player::TACTICAL_ACTION:
		actionTaken = TacticalAction(gbo, clickedPos);
		break;
	default:
		break;
	}
	return actionTaken;
}

bool Player::StartAction(GameBoardObject* gbo)
{
	bool actionTaken = false;
	if (typeid(*gbo) == typeid(PassButton))
	{
		_playerHasPassed = true;
		actionTaken = true;
	}
	else if (typeid(*gbo) == typeid(Player))
	{
		if (this->_objectId == gbo->GetObjectID() && _commandPool > 0)
		{
			_actionState = TACTICAL_ACTION;
			_subActionState = ACTIVATE_A_SYSTEM;
			_commandPool--;
			CommandCounter commandCounter = CommandCounter(_color, _graphicalPos);
			_commandCounterVector.push_back(commandCounter);
			_selectedObject = this;
			actionTaken = true;
		}
	}
	return actionTaken;
}

bool Player::TacticalAction(GameBoardObject* gbo, TupleInt clickedPos)
{
	bool actionTaken = false;
	switch (_subActionState)
	{
	case Player::NONE:
		break;
	case Player::ACTIVATE_A_SYSTEM:
		if (typeid(*gbo) == typeid(MapTile))
		{
			//TODO checka så att det blir rätt maptile eftersom att de överlappar
			_subActionState = MOVE_SHIPS_INTO_THE_SYSTEM;
			SetCommandCounterPos(gbo->GetGraphicalPos() + 
				_commandCounterVector[_commandCounterVector.size() -1].GetRelativePos(_homeSystem));
			_activatedSystem = static_cast<MapTile*>(gbo);
			_selectedObject = gbo;
			actionTaken = true;
		}
		break;
	case Player::MOVE_SHIPS_INTO_THE_SYSTEM:
		if (typeid(*gbo) == typeid(MapTile) && _menu.GetMenuState() == Menu::NoMenu)
		{
			_menu.SetMenuState(Menu::MoveUnits);
			MapTile* clickedSystem = static_cast<MapTile*>(gbo);
			_menu.SetUnitStackPointer(&_unitMap[clickedSystem->GetTilePos()], &_unitMap[_activatedSystem->GetTilePos()]);
			//TODO gör så att man kollar på movement för skeppen
			/*if (_activatedSystem->CalculateDistanceToTile(clickedSystem) == 1)
			{*/
				//TODO gör så att man kan välja vilka gubbar man ska flytta
			
								
			//}
			actionTaken = true;
		}
		else if (typeid(*gbo) == typeid(Menu) && _menu.GetMenuState() != Menu::NoMenu && _menu.GetObjectID() == gbo->GetObjectID())
		{
			_menu.Pressed(clickedPos);
			actionTaken = true;
		}
		else if (typeid(*gbo) == typeid(Player))
		{
			_menu.SetMenuState(Menu::NoMenu);
			_subActionState = PDS_FIRE;
			actionTaken = true;
		}
		break;
	case Player::PDS_FIRE:
		_subActionState = SPACE_BATTLE;
		actionTaken = true;
		break;
	case Player::SPACE_BATTLE:
		_subActionState = PLANETARY_LANDING;
		actionTaken = true;
		break;
	case Player::PLANETARY_LANDING:
		_subActionState = INVASION_COMBAT;
		actionTaken = true;
		break;
	case Player::INVASION_COMBAT:
		_subActionState = PRODUCE_UNITS;
		actionTaken = true;
		break;
	default:
		break;
	}
	return actionTaken;
}

void Player::SetCommandCounterPos(TupleInt pos)
{
	_commandCounterVector[_commandCounterVector.size() - 1].SetGraphicalPos(pos);
}

void Player::Save(TIParserNS::ListNode** playerNode) const
{
	*playerNode = new TIParserNS::ListNode(_race.GetRaceName());

	//playerOrder
	TIParserNS::ListNode* posInPlayerOrderNodeName = new TIParserNS::ListNode("playerOrder");
	TIParserNS::ListNode* posInPlayerOrderNodeData = new TIParserNS::ListNode(_posInPlayerOrder);
	posInPlayerOrderNodeName->SetChild(posInPlayerOrderNodeData);
	(*playerNode)->SetChild(posInPlayerOrderNodeName);

	//color
	TIParserNS::ListNode* colorNodeName = new TIParserNS::ListNode("color");
	TIParserNS::ListNode* colorNodeData = new TIParserNS::ListNode(_color);
	colorNodeName->SetChild(colorNodeData);
	posInPlayerOrderNodeName->SetNext(colorNodeName);

	//homeSystem
	TIParserNS::ListNode* homeSystemNodeName = new TIParserNS::ListNode("homeSystem");
	TIParserNS::ListNode* homeSystemNodeData = _homeSystem.ToListNode();
	homeSystemNodeName->SetChild(homeSystemNodeData);
	colorNodeName->SetNext(homeSystemNodeName);

	//Planets
	TIParserNS::ListNode* planetsNode = new TIParserNS::ListNode("Planets");
	homeSystemNodeName->SetNext(planetsNode);

	std::map<std::string, PlanetContainer>::const_iterator it;
	TIParserNS::ListNode* currentNode = new TIParserNS::ListNode("");
	TIParserNS::ListNode* oldNode = NULL;
	for (it = _planets.begin(); it != _planets.end(); it++)
	{
		currentNode = new TIParserNS::ListNode(it->second.GetPlanet()->GetName());
		if (oldNode == NULL) //TODO kan man göra detta på ett snyggare sätt?
		{
			planetsNode->SetChild(currentNode);
		}
		else
		{
			oldNode->SetNext(currentNode);
		}
		oldNode = currentNode;
	}

	//unitMap
	TIParserNS::ListNode* unitMapNode = new TIParserNS::ListNode("UnitMap");
	planetsNode->SetNext(unitMapNode);

	std::map<TupleInt, UnitStack>::const_iterator unitMapIt;
	currentNode = new TIParserNS::ListNode("");
	oldNode = NULL;
	for (unitMapIt = _unitMap.begin(); unitMapIt != _unitMap.end(); unitMapIt++)
	{
		currentNode = unitMapIt->second.ToListNode(unitMapIt->first.ToListNode());
		if (oldNode == NULL) //TODO kan man göra detta på ett snyggare sätt?
		{
			unitMapNode->SetChild(currentNode);
		}
		else
		{
			oldNode->SetNext(currentNode);
		}
		oldNode = currentNode;
	}
}