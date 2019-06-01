#ifndef UTILITY_CLASSES_H
#define UTILITY_CLASSES_H

#include "TIParser.h"

#include <utility>

class TupleInt : public std::pair<int, int>
{

public:
	TupleInt()
	{}

	TupleInt(int, int);

	int GetX() const;
	int GetY() const;

	TupleInt operator+(TupleInt) const;
	TupleInt operator-(TupleInt) const;
	TupleInt operator*(double) const;
	// TODO använd operator/ istället
	TupleInt Division(double) const;

	TIParserNS::ListNode* ToListNode() const;
};

#endif // !UTILITY_CLASSES_H