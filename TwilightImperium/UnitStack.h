#ifndef UNIT_H
#define UNIT_H

#include "GameBoardObject.h"

#include <string>

class UnitStack
{
public: 
	enum UnitType { Carrier, Cruiser, Destroyer, Dreadnought, Fighter, GroundForce, PDS, SpaceDock, WarSun };

// TODO Behövs detta?
/*protected:
	std::string _name;
	int _cost;
	int _unitsAvailable;
	int _battle;
	int _movement;*/

public:
	UnitStack(); //TODO behövs denna?
	//UnitStack(std::string, int, int, int, int, TupleInt, std::string, TupleInt);
	UnitStack(const UnitStack&);
	UnitStack& operator=(const UnitStack&);
	void CopyUnitStack(const UnitStack&);

	~UnitStack();

	void AddUnits(UnitType, int);

	//TODO remove
	/*std::string GetName();
	int GetCost();
	int GetUnitsAvailable();
	int GetBattle();
	int GetMovement();*/

private:
	int _numberOfCarriers = 0;
	int _numberOfCruisers = 0;
	int _numberOfDestroyers = 0;
	int _numberOfDreadnoughts = 0;
	int _numberOfFighters = 0;
	int _numberOfGroundForces = 0;
	int _numberOfPDS = 0;
	int _numberOfSpaceDocks = 0;
	int _numberOfWarSuns = 0;
};

#endif // !UNIT_H
