#ifndef UNIT_H
#define UNIT_H

#include "GameBoardObject.h"

#include <string>

class Unit : GameBoardObject
{
private:
	static const std::string _dataFile;

protected:
	std::string _name;
	int _cost;
	int _unitsAvailable;
	int _battle;
	int _movement;

public:
	Unit(); //TODO behövs denna?
	Unit(std::string, int, int, int, int);
	Unit(const Unit&);
	Unit& operator=(const Unit&);
	void CopyUnit(const Unit&);

	~Unit();

	std::string GetName();
	int GetCost();
	int GetUnitsAvailable();
	int GetBattle();
	int GetMovement();
};

#endif // !UNIT_H
