#include "UtilityClasses.h"

TupleInt::TupleInt(int xIn, int yIn) :
	std::pair<int, int>(xIn, yIn)
{}

int TupleInt::GetX() const
{
	return first;
}

int TupleInt::GetY() const 
{
	return second;
}

TupleInt TupleInt::operator+(TupleInt tupleIntInput) const //TODO kolla igenom vilka funktioner som ska vara const
{
	TupleInt tupleIntRes;
	tupleIntRes.first = first + tupleIntInput.first;
	tupleIntRes.second = second + tupleIntInput.second;
	return tupleIntRes;
}

TupleInt TupleInt::operator-(TupleInt tupleIntInput) const
{
	TupleInt tupleIntRes;
	tupleIntRes.first = first - tupleIntInput.first;
	tupleIntRes.second = second - tupleIntInput.second;
	return tupleIntRes;
}

TupleInt TupleInt::operator*(double multiplier) const
{
	TupleInt tupleIntRes;
	tupleIntRes.first = static_cast<int>(first* multiplier);
	tupleIntRes.second = static_cast<int>(second* multiplier);
	return tupleIntRes;
}

TupleInt TupleInt::Division(double denominator) const
{
	TupleInt res;
	res.first = static_cast<int>(first / denominator);
	res.second = static_cast<int>(second / denominator);
	return res;
}