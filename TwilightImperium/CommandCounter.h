#ifndef COMMAND_COUNTER_H
#define COMMAND_COUNTER_H

#include "GameBoardObject.h"

class CommandCounter : public GameBoardObject
{
private:
	GraphicsNS::Graphics::Color _color;

	static const TupleInt _imageSize;
	static const std::string _imagePath;

public:
	CommandCounter(GraphicsNS::Graphics::Color, TupleInt);
	CommandCounter& operator=(const CommandCounter&);
	CommandCounter(CommandCounter const&);
	~CommandCounter();

private:
	void DrawObject();
};

#endif // !COMMAND_COUNTER_H
