#ifndef PLAYER_H
#define PLAYER_H

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
	//TODO kan man använda color från graphics istället?
	enum Color { Red, Blue, White, Yellow, Green, Purple}; //TODO stora bokstäver? fyll på med färg

private:
	std::map<TupleInt, UnitStack> _unitMap;

	Player::Color _color;
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
	static const TupleInt _playerSheetSize;
	static const TupleInt _playerMetricFirstPos;
	static const TupleInt _playerMetricDiffPos;
	static const TupleInt _commandCounterPos;


	GraphicsNS::Image* _shipIndicator;
	static const std::string _shipIndicatorPath;
	const int _shipIndicatorSize = 10;

	//TODO förbättra indikationen, byt ut mot en flagga
	const int _planetIndicatorSize = 7;

public:
	Player(Race::RaceEnum, Player::Color, const std::map<TupleInt, MapTile>*, int);
	Player& operator=(const Player&);
	Player(Player const&);
	~Player();

	void PrepareForGameRound();

private:
	void CopyPlayer(Player const&);
	void SetStartPlanets(TIParserNS::ListNode*, const std::map<TupleInt, MapTile>*);
	void SetStartUnits(TIParserNS::ListNode*);
	void SetPlayerImage(TIParserNS::ListNode*);

	void DrawObject();
	void DrawPlanetMarkers(D3DCOLOR);
	void DrawUnits(D3DCOLOR);
	void DrawPlayerSheet(D3DCOLOR);

	void ResetPlanets();
	int CalculateResources();
	int CalculateInfluence();
};

#endif // !PLAYER_H