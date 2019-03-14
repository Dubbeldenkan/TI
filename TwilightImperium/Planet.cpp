#include "Planet.h"

Planet::Planet()
{}

Planet::Planet(std::string name, int resourceValue, int influenceValue, std::string techSpec)
{
	_name = name;
	_resourceValue = resourceValue;
	_influenceValue = influenceValue;

	if (techSpec.compare("Blue") == 0)
	{
		_technologySpeciality = Planet::Blue;
	}
	else if (techSpec.compare("Green") == 0)
	{
		_technologySpeciality = Planet::Green;
	}
	else if (techSpec.compare("Red") == 0)
	{
		_technologySpeciality = Planet::Red;
	}
	else if (techSpec.compare("Yellow") == 0)
	{
		_technologySpeciality = Planet::Yellow;
	}
	else if (techSpec.compare("None") == 0)
	{
		_technologySpeciality = Planet::None;
	}
	else
	{
		//TODO sätt in en try catch runt den här
		int temp = 1;
	}
}

Planet::~Planet()
{}