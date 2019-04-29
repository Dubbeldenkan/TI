#ifndef PLAYER_H
#define PLAYER_H

#include "CommandCounter.h"
#include "GameMap.h"
#include "MapTile.h"
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
	enum PlayerActionState {NONE, TACTICAL_ACTION};

private:
	std::map<TupleInt, UnitStack> _unitMap;
	std::vector<CommandCounter> _commandCounterVector;

	GraphicsNS::Graphics::Color _color;
	Race _race;
	std::map<std::string, PlanetContainer> _planets;
	TupleInt _homeSystem;

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

	GraphicsNS::Image* _shipIndicator;
	static const std::string _shipIndicatorPath;
	const int _shipIndicatorSize = 10;

	//TODO förbättra indikationen, byt ut mot en flagga
	const int _planetIndicatorSize = 7;

	bool _playerHasPassed;
	PlayerActionState _playerActionState = NONE;

public:
	Player(Race::RaceEnum, GraphicsNS::Graphics::Color, const std::map<TupleInt, MapTile>*, int);
	Player& operator=(const Player&);
	Player(Player const&);
	~Player();

	void PrepareForGameRound();

	bool TurnIsFinished() const;
	int GetPosInPlayerOrder() const;
	bool GetPlayerHasPassed() const;
	PlayerActionState GetPlayerActionState() const;
	
	void Action(GameBoardObject*);

	void SetToPassed();
	void SetCommandCounterPos(TupleInt);

private:
	void CopyPlayer(Player const&);
	void SetStartPlanets(TIParserNS::ListNode*, const std::map<TupleInt, MapTile>*);
	void SetStartUnits(TIParserNS::ListNode*);
	void SetPlayerImage(TIParserNS::ListNode*);

	void DrawObject();
	void DrawPlanetMarkers();
	void DrawUnits();
	void DrawPlayerSheet();

	void ResetPlanets();
	int CalculateResources();
	int CalculateInfluence();
};

#endif // !PLAYER_H