#ifndef UNIT_H
#define UNIT_H

#include "GameBoardObject.h"

#include <string>

class UnitStack
{
public: 
	enum UnitType { Carrier, Cruiser, Destroyer, Dreadnought, Fighter, GroundForce, PDS, SpaceDock, WarSun };

public:
	UnitStack();
	UnitStack(const UnitStack&);
	UnitStack& operator=(const UnitStack&);
	void CopyUnitStack(const UnitStack&);
	~UnitStack();

	bool AddUnits(std::string, int);
	//använd både till att lägga till och ta bort gubbar, om UnitStack är tom returneras true
	bool AddUnits(UnitType, int);
	int GetSum() const;

	TIParserNS::ListNode* ToListNode(TIParserNS::ListNode*) const;

private:
	std::map<UnitType, int> _unitMap;
};

#endif // !UNIT_H
