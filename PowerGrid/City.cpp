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

int City::GetRegion()
{
	return _region;
}

int City::GetCostForFirstFreePos(int gameStep)
{
	int result;
	if (_posColor[0] == none)
	{
		result = _cityCost[0];
	}
	else if ((_posColor[1] == none) && (gameStep > 1))
	{
		result = _cityCost[1];
	}
	else if ((_posColor[2] == none) && (gameStep > 2))
	{
		result = _cityCost[2];
	}
	else
	{
		result = 0;
	}
	return result;
}

void City::SetFirstFreePos(int colorInt)
{
	Color color = (Color) colorInt;
	for (int index = 0; index < numberOfHouses; index++)
	{
		if (_posColor[index] == none)
		{
			_posColor[index] = color;
			break;
		}
	}
}

City::Color City::GetColorForPos(int pos)
{
	return _posColor[pos];
}

int City::CheckIfCityIsOccupied(int gameStep)
{
	bool result = false;
	if (_posColor[0] == none)
	{
		result = _cityCost[0];
	}
	else if (_posColor[1] == none && gameStep > 1)
	{
		result = _cityCost[1];
	}
	else if (_posColor[2] == none && gameStep > 2)
	{
		result = _cityCost[2];
	}
	return result;
}