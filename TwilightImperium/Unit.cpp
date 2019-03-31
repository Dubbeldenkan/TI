#include "Unit.h"

Unit::Unit()
{}

Unit::Unit(std::string name, int cost, int unitsAvailable, int battle, int movement)
{
	_name = name;
	_cost = cost;
	_unitsAvailable = unitsAvailable;
	_battle = battle;
	_movement = movement;
}

Unit::Unit(const Unit& unit) : 
	GameBoardObject(unit._graphicalPos, unit._image)
{
	CopyUnit(unit);
}

Unit& Unit::operator=(const Unit& unit)
{
	CopyUnit(unit);
	return *this;
}

void Unit::CopyUnit(const Unit& unit)
{
	_name = unit._name;
	_cost = unit._cost;
	_unitsAvailable = unit._unitsAvailable;
	_battle = unit._battle;
	_movement = unit._movement;
}

//TODO görs detta korrekt eller är det minnesläckor då man tar bort gubbar
Unit::~Unit()
{}

std::string Unit::GetName()
{
	return _name;
}

int Unit::GetCost()
{
	return _cost;
}

int Unit::GetUnitsAvailable()
{
	return _unitsAvailable;
}

int Unit::GetBattle()
{
	return _battle;
}

int Unit::GetMovement()
{
	return _movement;
}