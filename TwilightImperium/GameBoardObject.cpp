#include "GameBoardObject.h"

int GameBoardObject::_latestObjectId = 0;
std::map<int, GameBoardObject*> GameBoardObject::_gameBoardObjects;
GraphicsNS::Graphics* GameBoardObject::_g = NULL;

GameBoardObject::GameBoardObject() : 
	_objectId(++_latestObjectId)
{}

GameBoardObject::GameBoardObject(TupleInt graphicalPos, GraphicsNS::Image image) :
	_objectId(++_latestObjectId)
{
	_graphicalPos = graphicalPos;
	_image = image;
	_gameBoardObjects[_objectId] = this;
}


GameBoardObject::GameBoardObject(TupleInt graphicalPos, TupleInt imageSize, std::string imagePath) :
	_objectId(++_latestObjectId)
{
	_graphicalPos = graphicalPos;
	_g->LoadImageFromFile(imagePath, &_image, imageSize.GetX(), imageSize.GetY());
	_gameBoardObjects[_objectId] = this;
}

GameBoardObject::~GameBoardObject()
{
	_gameBoardObjects.erase(_objectId); //TODO fix this
}

void GameBoardObject::DrawObject()
{
	_g->Draw(&_image, _graphicalPos.GetX(), _graphicalPos.GetY(), 1); //TODO kolla på om man ska ändra 1. 
}

void GameBoardObject::DrawAllObjects()
{
	_g->Clear();
	_g->StartDrawing();
	std::map<int, GameBoardObject*>::iterator it;
	for (it = _gameBoardObjects.begin(); it != _gameBoardObjects.end(); it++)
	{
		it->second->DrawObject();
	}
	_g->StopDrawing();
	_g->Flip();
}

void GameBoardObject::SetGraphics(HWND* hWnd)
{
	_g = new GraphicsNS::Graphics(*hWnd);
}