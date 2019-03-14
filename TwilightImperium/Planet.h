#ifndef PLANET_H
#define PLANET_H

#include <string>

class Planet
{
public:
	enum TechnologySpeciality {None, Red, Blue, Green, Yellow};

private:
	std::string _name;
	int _resourceValue;
	int _influenceValue;
	TechnologySpeciality _technologySpeciality;

public:
	Planet();
	Planet(std::string, int, int, std::string);

	~Planet();
};

#endif // !PLANET_H