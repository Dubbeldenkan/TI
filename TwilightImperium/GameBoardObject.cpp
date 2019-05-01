#include "GameBoardObject.h"

int GameBoardObject::_latestObjectId = 0;
std::map<int, GameBoardObject*> GameBoardObject::_gameBoardObjects;
GraphicsNS::Graphics* GameBoardObject::_g = NULL;
GameBoardObject* GameBoardObject::_selectedObject = NULL;

//Objects graphical position
const TupleInt GameBoardObject::_gameMapPos = TupleInt(-60, 0);
const TupleInt GameBoardObject::_playerSheetPos = TupleInt(590, 0);
const TupleInt GameBoardObject::_passButtonPos = TupleInt(960, 20);

const TupleInt GameBoardObject::_playerSheetSize = TupleInt(350, 120);

const TupleInt GameBoardObject::_unitPosInTile = TupleInt(25, 60);

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
	/*if (_selectedObject != NULL) //TODO fixa detta
	{
		_selectedObject->DrawSelectedObject();
	}*/
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

int GameBoardObject::GetObjectID() const
{
	return _objectId;
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

bool GameBoardObject::PosInObject(TupleInt pos)
{
	bool withInX = ((_graphicalPos.GetX() <= pos.GetX()) &&
		(pos.GetX() <= (_graphicalPos.GetX() + _image->GetXSize())));
	bool withInY = ((_graphicalPos.GetY() <= pos.GetY()) &&
		(pos.GetY() <= (_graphicalPos.GetY() + _image->GetYSize())));
	return (withInX && withInY);
}

void GameBoardObject::DrawSelectedObject()
{
	// TODO, ändra pekare till vector av pekare för att kunna markera flera
	float scalingFactor = 1.05f;
	//flytta x till vänster skillnaden mellan skalad storlek och normal storlek delat på 2
	//TODO borde detta castas till en float?
	int x = _graphicalPos.GetX() - ((_image->GetXSize() * scalingFactor) - (_image->GetXSize())) / 2; 
	int y = _graphicalPos.GetY() - ((_image->GetYSize() * scalingFactor) - (_image->GetYSize())) / 2;
	_g->DrawWithColor(_image, x, y, GraphicsNS::Graphics::BLUE, scalingFactor);
	DrawObject();
}