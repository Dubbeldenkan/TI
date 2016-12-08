#include "Logger.h"

Logger::Logger()
{
	_fileName = "";
}

Logger::Logger(char* playerName)
{
	_fileName += "LogFiles/";
	_fileName += playerName;
	_fileName += "LogFile.txt";

	_fs.open(_fileName, std::fstream::in | std::fstream::app);

	time_t now = time(0);
	char timeChar[26];
	ctime_s(timeChar, sizeof(timeChar), &now);
	_fs << std::endl << std::endl << "Filen skapades " << timeChar << std::endl;

	_fs.close();
}

Logger::Logger(std::string playerName)
{
	_fileName += "LogFiles/";
	_fileName += playerName;
	_fileName += "LogFile.txt";

	_fs.open(_fileName, std::fstream::in | std::fstream::app);

	time_t now = time(0);
	char timeChar[26];
	ctime_s(timeChar, sizeof(timeChar), &now);
	_fs << std::endl << std::endl << "Filen skapades " << timeChar << std::endl;

	_fs.close();
}

void Logger::Log(std::string input)
{
	_fs.open (_fileName, std::fstream::in | std::fstream::app);
	
	std::string str = input;
	time_t now = time(0);
	char timeChar[26];
	ctime_s(timeChar, sizeof(timeChar), &now);
	std::string timeString(timeChar);
	timeString = timeString.substr(11, 8);

	_fs << timeString << "   " << str << std::endl;

	_fs.close();
}