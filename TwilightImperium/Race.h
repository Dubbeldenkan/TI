#ifndef RACE_H
#define RACE_H

#include <string>

class Race
{
public:
	enum RaceEnum {BaronyOfLetnev, EmiratesOfHacan, FederationOfSol, L1Z1XMindnet, MentakCoalition, NaaluCollective};
private:
	std::string _dataFilePath;

public:
	Race();
	Race(std::string);
	Race &Race::operator=(const Race&);

	~Race();

	std::string GetDataFilePath() const;

	static Race CreateRace(RaceEnum);
};

class BaronyOfLetnev : public Race
{
private:
	static const std::string _dataFilePathValue;
public:
	BaronyOfLetnev();
};

class EmiratesOfHacan : public Race
{
private:
	static const std::string _dataFilePathValue;
public: EmiratesOfHacan();
};

class FederationOfSol : public Race
{
private:
	static const std::string _dataFilePathValue;
public: FederationOfSol();
};

class L1Z1XMindnet: public Race
{
private:
	static const std::string _dataFilePathValue;
public: L1Z1XMindnet();
};

class MentakCoalition : public Race
{
private:
	static const std::string _dataFilePathValue;
public: MentakCoalition();
};

class NaaluCollective : public Race
{
private:
	static const std::string _dataFilePathValue;
public: NaaluCollective();
};

#endif // !RACE_H