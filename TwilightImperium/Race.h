#ifndef RACE_H
#define RACE_H

#include <string>

class Race
{
public:
	enum RaceEnum {BaronyOfLetnev, };
private:
	std::string _dataFilePath;

public:
	Race();
	Race(std::string);
	Race &Race::operator=(const Race&);

	~Race();

	std::string GetDataFilePath() const;
};

class BaronyOfLetnev : public Race
{
private:
	static const std::string _dataFilePathValue;
public:
	BaronyOfLetnev();

};

#endif // !RACE_H