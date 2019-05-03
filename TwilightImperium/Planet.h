#ifndef PLANET_H
#define PLANET_H

#include "GameBoardObject.h"

#include <string>

class Planet : public GameBoardObject
{
public:
	enum TechnologySpeciality {None, Red, Blue, Green, Yellow};
	static const TupleInt _imageSize;

private:
	std::string _name;
	int _resourceValue;
	int _influenceValue;
	TechnologySpeciality _technologySpeciality;

	static const std::string _imagePath;
	static const int _layerValue;

public:
	Planet();
	Planet& operator=(const Planet&);
	Planet(Planet const&);
	Planet(std::string, int, int, std::string);

	~Planet();

	std::string GetName() const;
	int GetResources() const;
	int GetInfluence() const;

private:
	void CopyPlanet(Planet const&);
	void DrawObject();
};

#endif // !PLANET_H