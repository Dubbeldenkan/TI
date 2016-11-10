#include "City.h"

City::City(char* cityName, int region, int xPos, int yPos)
{
	_cityName = cityName;
	_region = region;
	_xPos = xPos;
	_yPos = yPos;
}

char* City::GetName()
{
	return _cityName;
}

int City::GetXPos()
{
	return _xPos;
}

int City::GetYPos()
{
	return _yPos;
}