#ifndef HELP_STRUCTS_H
#define HELP_STRUCTS_H

#include <utility>

struct TupleInt
{
	std::pair<int, int> _pair;

	TupleInt()
	{
	}

	TupleInt(int xIn, int yIn)
	{
		_pair = std::make_pair(xIn, yIn);
	}

	int GetX()
	{
		return _pair.first;
	}

	int GetY()
	{
		return _pair.second;
	}
};

#endif // !HELP_STRUCTS_H