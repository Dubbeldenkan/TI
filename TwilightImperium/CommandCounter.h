#ifndef COMMAND_COUNTER_H
#define COMMAND_COUNTER_H

#include "GameBoardObject.h"

class CommandCounter : public GameBoardObject
{
private:
	GraphicsNS::Graphics::Color _color;

	static const TupleInt _imageSize;
	static const std::string _imagePath;

	const TupleInt _commandCounterPos[6] = { TupleInt(25, 0), TupleInt(55, 0), TupleInt(75, 35),
		TupleInt(55, 70), TupleInt(25, 70), TupleInt(5, 35) };
public:
	CommandCounter(GraphicsNS::Graphics::Color, TupleInt);
	CommandCounter& operator=(const CommandCounter&);
	CommandCounter(CommandCounter const&);
	~CommandCounter();

	TupleInt GetRelativePos(TupleInt);
private:
	void DrawObject();
};

#endif // !COMMAND_COUNTER_H
