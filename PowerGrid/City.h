#ifndef CITY_H
#define CITY_H

class City
{
public:
	enum Color { red, blue, yellow, black, green, purple, none };
private:
	const static int numberOfHouses = 3;
	char* _cityName;
	int _region;
	int _xPos;
	int _yPos;
	Color _posColor[numberOfHouses] = { none, none, none };
	int _cityCost[numberOfHouses] = { 10, 15, 20 };

public:
	City(char*, int, int, int);
	~City() {};

	int GetXPos();
	int GetYPos();
	int GetRegion();
	char* GetName();
	int GetCostForFirstFreePos(int);
	void SetFirstFreePos(int);
	Color GetColorForPos(int);
	int CheckPriceForCity(int);
	bool PlayerAlreadyHasCity(City::Color);
};

#endif // !CITY_H