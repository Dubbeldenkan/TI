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

	//Objects graphical position
	static const TupleInt _mapPos;

public:
	GameBoardObject();
	GameBoardObject(TupleInt, GraphicsNS::Image);
	GameBoardObject(TupleInt, TupleInt, std::string);
	~GameBoardObject();
	
	void DrawObject();

	static void DrawAllObjects();

	static void SetGraphics(HWND* hWnd);

	static TupleInt GetMapPos();

	void SetGraphicalPos(TupleInt);
};

#endif // ! GAME_BOARD_OBJECT_H

