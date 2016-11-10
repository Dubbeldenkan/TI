#ifndef CITY_H
#define CITY_H

class City
{
	char* _cityName;
	int _region;
	int _xPos;
	int _yPos;

public:
	City(char*, int, int, int);
	~City() {};

	int GetXPos();
	int GetYPos();
	char* GetName();
};

#endif // !CITY_H