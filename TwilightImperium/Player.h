#ifndef PLAYER_H
#define PLAYER_H

#include "CommandCounter.h"
#include "GameMap.h"
#include "MapTile.h"
#include "Menu.h"
#include "PassButton.h"
#include "Race.h"
#include "TIParser.h"
#include "UnitStack.h"

#include <memory>

struct PlanetContainer
{
private:
	const Planet* _planet;
	bool _exhausted = true;
public:
	PlanetContainer(const Planet*);
	const Planet* GetPlanet() const;

	void SetToExhausted();
	void UnsetExhausted();
};

class Player : public GameBoardObject
{
public:
	enum ActionState {START_ACTION, TACTICAL_ACTION};
	enum SubActionState {NONE, ACTIVATE_A_SYSTEM, MOVE_SHIPS_INTO_THE_SYSTEM, PDS_FIRE, SPACE_BATTLE, PLANETARY_LANDING, 
		INVASION_COMBAT, PRODUCE_UNITS};

private:
	std::map<TupleInt, UnitStack> _unitMap;
	std::vector<CommandCounter> _commandCounterVector;
	MapTile* _activatedSystem = NULL;

	GraphicsNS::Graphics::Color _color;
	Race _race;
	std::map<std::string, PlanetContainer> _planets;
	TupleInt _homeSystem;
	Menu _menu = Menu();

	int _strategyAllocation = 2;
	int _fleetSupply = 3;
	int _commandPool = 3;
	int _tradeGoods = 0;
	int _resources = 0;
	int _influence = 0;

	//Position of player in player sheet list
	int _posInPlayerOrder;
	static const TupleInt _playerMetricFirstPos;
	static const TupleInt _playerMetricDiffPos;
	static const TupleInt _commandCounterMetricPos;

	const std::string _playerSheetPath = "Race/PlayerSheet.png";

	GraphicsNS::Image* _shipIndicator;
	static const std::string _shipIndicatorPath;
	static const GameBoardObject::LayerEnum _layerValue = GameBoardObject::PlayerLayer;
	const int _shipIndicatorSize = 10;

	//TODO förbättra indikationen, byt ut mot en flagga
	const int _planetIndicatorSize = 7;

	bool _playerHasPassed;

	ActionState _actionState = ActionState::START_ACTION;
	SubActionState _subActionState = SubActionState::NONE;

public:
	Player(Race::RaceEnum, GraphicsNS::Graphics::Color, const GameMap*, int);
	Player(TIParserNS::ListNode*, const GameMap*);

	Player& operator=(const Player&);
	Player(Player const&);
	~Player();

	void PrepareForGameRound();

	bool TurnIsFinished() const;
	int GetPosInPlayerOrder() const;
	bool GetPlayerHasPassed() const;
	ActionState GetActionState() const;
	SubActionState GetSubActionState() const;
	
	void Action(GameBoardObject*);
	void Save(TIParserNS::ListNode**) const;

	void SetCommandCounterPos(TupleInt);

private:
	void CopyPlayer(Player const&);
	void SetStartPlanets(TIParserNS::ListNode*, const GameMap*);
	void SetStartUnits(TIParserNS::ListNode*);
	void SetPlayerImage(TIParserNS::ListNode*);

	void DrawObject();
	void DrawPlanetMarkers();
	void DrawUnits();
	void DrawPlayerSheet();

	void ResetPlanets();
	int CalculateResources();
	int CalculateInfluence();

	void StartAction(GameBoardObject*);
	void TacticalAction(GameBoardObject*);
};

#endif // !PLAYER_H