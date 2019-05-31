#include "GameBoardObject.h"

int GameBoardObject::_latestObjectId = 0;
std::map<int, GameBoardObject*> GameBoardObject::_gameBoardObjects;
GraphicsNS::Graphics* GameBoardObject::_g = NULL;
GameBoardObject* GameBoardObject::_selectedObject = NULL;
const int GameBoardObject::_numberOfLayers = 2;

//Objects graphical position
const TupleInt GameBoardObject::_gameMapPos = TupleInt(-60, 0);
const TupleInt GameBoardObject::_playerSheetPos = TupleInt(590, 0);
const TupleInt GameBoardObject::_passButtonPos = TupleInt(960, 20);

const TupleInt GameBoardObject::_playerSheetSize = TupleInt(350, 120);

const TupleInt GameBoardObject::_unitPosInTile = TupleInt(25, 60);

GameBoardObject::GameBoardObject() : _layer(0), _objectId(++_latestObjectId)
{
	_gameBoardObjects[_objectId] = this;
}

GameBoardObject::GameBoardObject(TupleInt graphicalPos, GraphicsNS::Image* image, int layer) :
	_layer(layer), _objectId(++_latestObjectId)
{
	_graphicalPos = graphicalPos;
	_image = image;
	_gameBoardObjects[_objectId] = this;
}

GameBoardObject::GameBoardObject(TupleInt graphicalPos, TupleInt imageSize, std::string imagePath, int layer) :
	_layer(layer), _objectId(++_latestObjectId)
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

	std::vector<GameBoardObject*> layerVector[_numberOfLayers];
	std::map<int, GameBoardObject*>::iterator it;
	for (it = _gameBoardObjects.begin(); it != _gameBoardObjects.end(); it++)
	{
		if(_selectedObject == NULL || it->second->GetObjectID() != _selectedObject->GetObjectID())
		{
			layerVector[it->second->_layer].push_back(it->second);
		}
	}
	for (int layerCount = 0; layerCount < _numberOfLayers; layerCount++)
	{
		for (int vectorCount = 0; vectorCount < static_cast<int>(layerVector[layerCount].size()); vectorCount++)
		{
			layerVector[layerCount][vectorCount]->DrawObject();
		}
		if (_selectedObject != NULL && _selectedObject->_layer == layerCount)
		{
			_selectedObject->DrawSelectedObject();
		}
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

int GameBoardObject::GetObjectID() const
{
	return _objectId;
}

void GameBoardObject::Save(TIParserNS::ListNode** savedGame) const
{}

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
	// TODO, �ndra pekare till vector av pekare f�r att kunna markera flera
	//flytta x till v�nster skillnaden mellan skalad storlek och normal storlek delat p� 2
	int xPos = _graphicalPos.GetX() - 
		static_cast<int>(((_image->GetXSize() * _selectecObjectScalingFactor) - (_image->GetXSize())) / 2);
	int yPos = _graphicalPos.GetY() - 
		static_cast<int>(((_image->GetYSize() * _selectecObjectScalingFactor) - (_image->GetYSize())) / 2);
	_g->DrawWithColor(_image, xPos, yPos, GraphicsNS::Graphics::BLUE, _selectecObjectScalingFactor);
	DrawObject();
}