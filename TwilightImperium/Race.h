#ifndef RACE_H
#define RACE_H

#include <string>
#include <map>

class Race
{
public:
	enum RaceEnum {BaronyOfLetnev, EmiratesOfHacan, FederationOfSol, L1Z1XMindnet, MentakCoalition, NaaluCollective};
private:
	static const std::map<std::string, std::string> _dataFilePathMap;
	std::string _raceName;

public:
	Race();
	Race(std::string);
	Race &Race::operator=(const Race&);

	~Race();

	std::string GetDataFilePath() const;
	std::string GetRaceName() const;

	static Race CreateRace(RaceEnum);

	static const std::map<std::string, std::string> CreateRaceNameMap();
};

class BaronyOfLetnev : public Race
{
public:
	static const std::string _raceNameValue;
public:
	BaronyOfLetnev();
};

class EmiratesOfHacan : public Race
{
public:
	static const std::string _raceNameValue;
public: EmiratesOfHacan();
};

class FederationOfSol : public Race
{
public:
	static const std::string _raceNameValue;
public: FederationOfSol();
};

class L1Z1XMindnet: public Race
{
public:
	static const std::string _raceNameValue;
public: L1Z1XMindnet();
};

class MentakCoalition : public Race
{
public:
	static const std::string _raceNameValue;
public: MentakCoalition();
};

class NaaluCollective : public Race
{
public:
	static const std::string _raceNameValue;
public: NaaluCollective();
};

#endif // !RACE_H