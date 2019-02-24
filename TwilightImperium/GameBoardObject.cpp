#include "GameBoardObject.h"

int GameBoardObject::_latestObjectId = 0;
std::map<int, GameBoardObject*> GameBoardObject::_gameBoardObjects;
GraphicsNS::Graphics* GameBoardObject::_g = NULL;

GameBoardObject::GameBoardObject(TupleInt graphicalPos, TupleInt imageSize, std::string imagePath) :
	_objectId(++_latestObjectId)
{
	_graphicalPos = graphicalPos;
	_g->LoadImageFromFile(imagePath, &_image, imageSize.GetX(), imageSize.GetY());
	_gameBoardObjects[_objectId] = this;
}


GameBoardObject::~GameBoardObject()
{
	_gameBoardObjects.erase(_objectId);
}

void GameBoardObject::DrawObject()
{
	
}

void GameBoardObject::DrawAllObjects()
{
	std::map<int, GameBoardObject*>::iterator it;
	for (it = _gameBoardObjects.begin(); it != _gameBoardObjects.end(); it++)
	{
		it->second->DrawObject();
	}
}

void GameBoardObject::SetGraphics(GraphicsNS::Graphics* g)
{
	_g = g;
}