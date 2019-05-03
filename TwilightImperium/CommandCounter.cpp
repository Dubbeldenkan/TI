#include "CommandCounter.h"

const TupleInt CommandCounter::_imageSize = TupleInt(20, 14);
const std::string CommandCounter::_imagePath = "Race/CommandCounter.png";
const int CommandCounter::_layerValue = 1;

CommandCounter::CommandCounter(GraphicsNS::Graphics::Color color, TupleInt pos) : _color(color),
	GameBoardObject(pos, _imageSize, _imagePath, _layerValue)
{}

CommandCounter& CommandCounter::operator=(const CommandCounter& commandCounter)
{
	_color = commandCounter._color;
	return *this;
}

CommandCounter::CommandCounter(const CommandCounter& commandCounter) :
	GameBoardObject(commandCounter._graphicalPos, commandCounter._image, _layerValue)
{
	_color = commandCounter._color;
}

CommandCounter::~CommandCounter()
{}

void CommandCounter::DrawObject()
{
	_g->DrawWithColor(_image, _graphicalPos.GetX(), _graphicalPos.GetY(), _color);
}

TupleInt CommandCounter::GetRelativePos(TupleInt playerPos)
{
	TupleInt tupleInt = _commandCounterPos[playerPos.second / 60];
	return tupleInt;
}