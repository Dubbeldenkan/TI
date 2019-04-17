#include "UnitStack.h"

UnitStack::UnitStack()
{}

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
	std::map<UnitStack::UnitType, int>::const_iterator it;
	for (it = unitStack._numberOfUnits.begin(); it != unitStack._numberOfUnits.end(); it++)
	{
		_numberOfUnits.insert(std::make_pair(it->first, it->second));
	}
}

//TODO görs detta korrekt?
UnitStack::~UnitStack()
{}

bool UnitStack::AddUnits(std::string unitName, int numberOfUnits)
{
	UnitStack::UnitType unitType;

	if (unitName.compare("Carrier") == 0)
	{
		unitType = UnitStack::Carrier;
	}
	else if (unitName.compare("Cruiser") == 0)
	{
		unitType = UnitStack::Cruiser;
	}
	else if (unitName.compare("Destroyer") == 0)
	{
		unitType = UnitStack::Destroyer;
	}
	else if (unitName.compare("Dreadnought") == 0)
	{
		unitType = UnitStack::Dreadnought;
	}
	else if (unitName.compare("GroundForce") == 0)
	{
		unitType = UnitStack::GroundForce;
	}
	else if (unitName.compare("SpaceDock") == 0)
	{
		unitType = UnitStack::SpaceDock;
	}
	else
	{
		int temp = 1; //TODO lägg till felhantering här
	}
	return AddUnits(unitType, numberOfUnits);
}

bool UnitStack::AddUnits(UnitStack::UnitType unitType, int numberOfUnits)
{
	bool stackEmpty = false;
	if (static_cast<bool>(_numberOfUnits.count(unitType)))
	{
		_numberOfUnits[unitType] = _numberOfUnits[unitType] + numberOfUnits;
	}
	else
	{
		_numberOfUnits.insert(std::make_pair(unitType, numberOfUnits));
	}
	if (_numberOfUnits[unitType] == 0)
	{
		_numberOfUnits.erase(unitType);
		if (_numberOfUnits.size() == 0)
		{
			stackEmpty = true;
		}
	}
	return stackEmpty;
}