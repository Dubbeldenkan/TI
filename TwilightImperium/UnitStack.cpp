#include "UnitStack.h"

UnitStack::UnitStack()
{}

//TODO remove
/*UnitStack::UnitStack(std::string name, int cost, int unitsAvailable, int battle, int movement, TupleInt imageSize, std::string filePath,
	TupleInt graphicalPos)
{
	_name = name;
	_cost = cost;
	_unitsAvailable = unitsAvailable;
	_battle = battle;
	_movement = movement;
}*/

UnitStack::UnitStack(const UnitStack& unitStack)
{
	CopyUnitStack(unitStack);
}

UnitStack& UnitStack::operator=(const UnitStack& unitStack)
{
	CopyUnitStack(unitStack);
	return *this;
}

void UnitStack::CopyUnitStack(const UnitStack& unitStack)
{
	_numberOfCarriers = unitStack._numberOfCarriers;
	_numberOfCruisers = unitStack._numberOfCruisers;
	_numberOfDestroyers = unitStack._numberOfDestroyers;
	_numberOfDreadnoughts = unitStack._numberOfDreadnoughts;
	_numberOfFighters = unitStack._numberOfFighters;
	_numberOfGroundForces = unitStack._numberOfGroundForces;
	_numberOfPDS = unitStack._numberOfPDS;
	_numberOfSpaceDocks = unitStack._numberOfSpaceDocks;
	_numberOfWarSuns = unitStack._numberOfWarSuns;
}

//TODO görs detta korrekt eller är det minnesläckor då man tar bort gubbar
UnitStack::~UnitStack()
{}

/*std::string UnitStack::GetName()
{
	return _name;
}

int UnitStack::GetCost()
{
	return _cost;
}

int UnitStack::GetUnitsAvailable()
{
	return _unitsAvailable;
}

int UnitStack::GetBattle()
{
	return _battle;
}

int UnitStack::GetMovement()
{
	return _movement;
}*/

void UnitStack::AddUnits(UnitStack::UnitType unitType, int numberOfUnits)
{
	switch (unitType)
	{
	case UnitStack::Carrier:
		_numberOfCarriers += numberOfUnits;
		break;
	case UnitStack::Cruiser:
		_numberOfCruisers += numberOfUnits;
		break;
	case UnitStack::Destroyer:
		_numberOfDestroyers += numberOfUnits;
		break;
	case UnitStack::Dreadnought:
		_numberOfDreadnoughts += numberOfUnits;
		break;
	case UnitStack::Fighter:
		_numberOfFighters += numberOfUnits;
		break;
	case UnitStack::GroundForce:
		_numberOfGroundForces += numberOfUnits;
		break;
	case UnitStack::PDS:
		_numberOfPDS += numberOfUnits;
		break;
	case UnitStack::SpaceDock:
		_numberOfSpaceDocks += numberOfUnits;
		break;
	case UnitStack::WarSun:
		_numberOfWarSuns += numberOfUnits;
		break;
	default:
		break;
	}
}