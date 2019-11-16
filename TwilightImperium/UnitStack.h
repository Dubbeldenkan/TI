#ifndef UNIT_H
#define UNIT_H

#include "GameBoardObject.h"

#include <string>

#define NUMBER_OF_UNIT_TYPES 9

class UnitStack
{
public: 
	enum UnitType { Carrier, Cruiser, Destroyer, Dreadnought, Fighter, GroundForce, PDS, SpaceDock, WarSun };

private:
	const int _numberOfUnitsTypes = NUMBER_OF_UNIT_TYPES;
	const std::string unitStrings[NUMBER_OF_UNIT_TYPES] = { "Carries", "Cruiser", "Destroyer", "Dreadnought",
		"Fighter", "GroundForce", "PDS", "Space dock", "War sun" };

	std::map<UnitType, int> _unitMap;

public:
	UnitStack();
	UnitStack(const UnitStack&);
	UnitStack(TIParserNS::ListNode*);
	UnitStack& operator=(const UnitStack&);
	void CopyUnitStack(const UnitStack&);
	~UnitStack();

	bool AddUnits(std::string, int);
	void AddUnits(UnitStack*);
	//använd både till att lägga till och ta bort gubbar, om UnitStack är tom returneras false
	bool AddUnits(UnitType, int);
	int GetSum() const;
	void Reset();

	int GetAmountOfAUnitType(UnitType);
	int GetNumberOfUnitsTypes() const;
	std::string GetUnitString(UnitType);

	TIParserNS::ListNode* ToListNode(TIParserNS::ListNode*) const;
};

#endif // !UNIT_H
