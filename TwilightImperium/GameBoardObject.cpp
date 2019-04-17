#include "GameBoardObject.h"

int GameBoardObject::_latestObjectId = 0;
std::map<int, GameBoardObject*> GameBoardObject::_gameBoardObjects;
GraphicsNS::Graphics* GameBoardObject::_g = NULL;

//Objects graphical position
const TupleInt GameBoardObject::_gameMapPos = TupleInt(0, 0);
const TupleInt GameBoardObject::_unitPosInTile = TupleInt(25, 60);

const TupleInt GameBoardObject::_playerSheetPos = TupleInt(650, 0);

GameBoardObject::GameBoardObject() : 
	_objectId(++_latestObjectId)
{
	_gameBoardObjects[_objectId] = this;
}

GameBoardObject::GameBoardObject(TupleInt graphicalPos, GraphicsNS::Image* image) :
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
	_image = _g->LoadImageFromFile(imagePath, imageSize.GetX(), imageSize.GetY());
	_gameBoardObjects[_objectId] = this;
}

GameBoardObject::~GameBoardObject()
{
	_gameBoardObjects.erase(_objectId);
}

void GameBoardObject::DrawObject()
{
	_g->Draw(_image, _graphicalPos.GetX(), _graphicalPos.GetY(), _scale);
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

TupleInt GameBoardObject::GetGameMapPos()
{
	return _gameMapPos;
}

TupleInt GameBoardObject::GetGraphicalPos() const
{
	return _graphicalPos;
}

void GameBoardObject::SetGraphicalPos(TupleInt pos)
{
	_graphicalPos = pos;
}

void GameBoardObject::SetImageScale(float scale)
{
	_scale = scale;
}

void GameBoardObject::SetImage(std::string imagePath, TupleInt imageSize)
{
	_image = _g->LoadImageFromFile(imagePath, imageSize.GetX(), imageSize.GetY());
}