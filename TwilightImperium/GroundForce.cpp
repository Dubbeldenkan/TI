#include "GroundForce.h"


const std::string GroundForce::_nameValue = "GroundForce";
const int GroundForce::_costValue = 1;
const int GroundForce::_unitsAvailableValue = 12;
const int GroundForce::_battleValue = 8;
const int GroundForce::_movementValue = 0;
const std::string GroundForce::_imagePathValue = "Unit/GroundForce.png";

GroundForce::GroundForce() :
	Unit(_nameValue, _costValue, _unitsAvailableValue, _battleValue, _movementValue)
{}