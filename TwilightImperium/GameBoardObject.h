#ifndef GAME_BOARD_OBJECT_H
#define GAME_BOARD_OBJECT_H

#include "Image.h"
#include "HelpStructs.h"
#include "Graphics.h"

#include <string>
#include <map>

class GameBoardObject
{
protected:
	TupleInt _graphicalPos;
	GraphicsNS::Image _image;
	const int _objectId;
	static GraphicsNS::Graphics* _g;

private:
	static int _latestObjectId;
	static std::map<int, GameBoardObject*> _gameBoardObjects;

public:
	GameBoardObject(TupleInt, TupleInt, std::string);
	~GameBoardObject();
	
	void DrawObject();

	static void DrawAllObjects();

	static void SetGraphics(GraphicsNS::Graphics*);
};

#endif // ! GAME_BOARD_OBJECT_H

