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
	//anv�nd b�de till att l�gga till och ta bort gubbar, om UnitStack �r tom returneras true
	bool AddUnits(UnitType, int);
	int GetSum() const;

	TIParserNS::ListNode* ToListNode(TIParserNS::ListNode*) const;

private:
	std::map<UnitType, int> _unitMap;
};

#endif // !UNIT_H
