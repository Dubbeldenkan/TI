#include "Planet.h"

Planet::Planet()
{}

Planet::Planet(std::string name, int resourceValue, int influenceValue, Planet::TechnologySpeciality technologySpeciality)
{
	_name = name;
	_resourceValue = resourceValue;
	_influenceValue = influenceValue;
	_technologySpeciality = technologySpeciality;
}

Planet::~Planet()
{}