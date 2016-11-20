#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Logger
{
	std::string _fileName;
	std::ofstream _fs;

public:
	Logger();
	Logger(char*);
	~Logger() {};

	void Log(std::string);
};
#endif // !LOGGER_H