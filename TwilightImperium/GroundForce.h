#ifndef GROUND_FORCE_H
#define GROUND_FORCE_H

#include "Unit.h"

#include <string>

class GroundForce : public Unit
{
private:
	static const std::string _nameValue;
	static const int _costValue;
	static const int _unitsAvailableValue;
	static const int _battleValue;
	static const int _movementValue;
	static const std::string _imagePathValue;

public:
	GroundForce();
};

#endif // !GROUND_FORCE_H