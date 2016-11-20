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
}

void Logger::Log(std::string input)
{
	_fs.open (_fileName, std::fstream::in | std::fstream::app);

	std::string str = input;
	_fs << str;

	_fs.close();
}