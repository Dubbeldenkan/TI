#ifndef PLAYER_H
#define PLAYER_H

#include "MapTile.h"
#include "Race.h"
#include "TIParser.h"
#include "UnitStack.h"

#include <memory>

class Player : public GameBoardObject
{
public:
	//TODO kan man använda color från graphics istället?
	enum Color { Red, Blue, Black, Yellow, Green, Orange}; //TODO stora bokstäver? fyll på med färg

private:
	std::map<TupleInt, UnitStack> _unitMap;

	Player::Color _color;
	Race _race;
	std::map<std::string, const Planet*> _planets; //TODO borde detta vara en vector istället?
	TupleInt _homeSystem;

	//TODO förbättra indikationen
	const int _planetIndicatorSize = 7;

public:
	Player(Race::RaceEnum, Player::Color, const std::map<TupleInt, MapTile>*);
	Player& operator=(const Player&);
	Player(Player const&);
	~Player();

private:
	void CopyPlayer(Player const&);
	void SetStartPlanets(TIParserNS::ListNode*, const std::map<TupleInt, MapTile>*);
	void SetStartUnits(TIParserNS::ListNode*);
	void SetPlayerImage(TIParserNS::ListNode*);

	void DrawObject();
	void DrawPlanetMarkers();
	void DrawUnits();
};

#endif // !PLAYER_H