#ifndef HELP_STRUCTS_H
#define HELP_STRUCTS_H

#include <utility>

struct TupleInt : public std::pair<int, int>
{
	TupleInt()
	{}

	TupleInt(int xIn, int yIn) :
		std::pair<int, int>(xIn, yIn)
	{}

	int GetX()
	{
		return first;
	}

	int GetY()
	{
		return second;
	}
};

#endif // !HELP_STRUCTS_H