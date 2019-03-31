#ifndef PLAYER_H
#define PLAYER_H

#include "GroundForce.h"
#include "Race.h"
#include "TIParser.h"
#include "MapTile.h"

#include <memory>

class Player
{
private:
	std::multimap<TupleInt, Unit> _unitMap;

	Race _race;
	std::vector<Planet*> _planets;

public:
	Player(Race::RaceEnum, std::map<TupleInt, MapTile>);
	~Player();

private:
	void SetStartPlanets(TIParserNS::ListNode*, std::map<TupleInt, MapTile>);
	void SetStartUnits(TIParserNS::ListNode*);
};

#endif // !PLAYER_H