#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>

class Logger
{
	std::string _fileName;
	std::ofstream _fs;
	const time_t ctt = time(0);

public:
	Logger();
	Logger(char*);
	~Logger() {};

	void Log(std::string);
};
#endif // !LOGGER_H