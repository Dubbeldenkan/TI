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
	for (it = unitStack._unitMap.begin(); it != unitStack._unitMap.end(); it++)
	{
		_unitMap.insert(std::make_pair(it->first, it->second));
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
	else if (unitName.compare("Fighter") == 0) //TODO denna borde inte vara med här
	{
		unitType = UnitStack::Fighter;
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
	if (static_cast<bool>(_unitMap.count(unitType)))
	{
		_unitMap[unitType] = _unitMap[unitType] + numberOfUnits;
	}
	else
	{
		_unitMap.insert(std::make_pair(unitType, numberOfUnits));
	}
	if (_unitMap[unitType] == 0)
	{
		_unitMap.erase(unitType);
		if (_unitMap.size() == 0)
		{
			stackEmpty = true;
		}
	}
	return stackEmpty;
}

int UnitStack::GetSum() const
{
	int sum = 0;
	std::map<UnitStack::UnitType, int>::const_iterator it;
	for (it = _unitMap.begin(); it != _unitMap.end(); it++)
	{
		sum += it->second;
	}
	return sum;
}